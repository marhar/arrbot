set baud 115200
set port [glob /dev/cu.usb*]
set current ""
set version ""

set mins [list]
set maxs [list]
set labels {- stickx sticky accelx accely accelz buttonz buttonc}

proc doread {fd} {
    # 0  1   2   3   4   5   6 7
    # n  130 132 306 539 580 0 0

    global line mins maxs labels
    global version current

    if {[gets $fd line] < 0} {
        puts "eof on read"
        close $::port
        exit 0
    }
    ##puts line=[llength $line],$line
    set cmdlen [llength $line]
    set cmdstr [lindex $line 0]
    if     {$cmdlen == 1 && [string equal $cmdstr "i"]} {
        # initialization
        set mins ""
        set maxs ""
        set version ""
        set current ""
    } elseif {$cmdlen == 8 && [string equal $cmdstr "n"]} {
        # nunchuck data
        if {[llength $mins] == 0} {
            set mins $line
        }
        if {[llength $maxs] == 0} {
            set maxs $line
        }

        foreach i {1 2 3 4 5} {
            .x$i set [lindex $line $i]
        }

        .cfg delete 0.0 end
        .cfg insert end "\n\n"

        foreach i {1 2 3 4 5 6 7} {
            if {[lrange $mins $i $i] > [lrange $line $i $i]} {
                set mins [lreplace $mins $i $i [lindex $line $i]]
            }
            if {[lrange $maxs $i $i] < [lrange $line $i $i]} {
                set maxs [lreplace $maxs $i $i [lindex $line $i]]
            }
            .cfg insert end "  min_"
            .cfg insert end [lindex $labels $i]
            .cfg insert end " = "
            .cfg insert end [lindex $mins $i]
            .cfg insert end ";    max_"
            .cfg insert end [lindex $labels $i]
            .cfg insert end " = "
            .cfg insert end [lindex $maxs $i]
            .cfg insert end ";\n"
        }

        set bz [lindex $line 6]
        set bc [lindex $line 7]
        if {$bz} { .bz configure -bg blue } else { .bz configure -bg lightblue }
        if {$bc} { .bc configure -bg blue } else { .bc configure -bg lightblue }

    } elseif {$cmdlen == 3 && [string equal $cmdstr "v"]} {
        # version
        set version $line
    } elseif {$cmdlen == 2 && [string equal $cmdstr "c"]} {
        # current config
        set current $line
    }
    update
}

wm protocol . WM_DELETE_WINDOW { puts closewin; close $::ser; exit 0 }

proc bgerror {msg} {
    global errorInfo
    close $::ser
    puts "I got an error in an event: $msg"
    puts "The stack trace was this:\n$errorInfo"
    exit 1
}

set ::ser [open $port r+]
fconfigure $::ser -mode $baud,n,8,1
fileevent $::ser readable "doread $::ser"

label .port -textvariable ::port -anchor w
label .version -textvariable ::version -anchor w
label .current -textvariable ::current -anchor w
label .line -textvariable ::line -anchor w
scale .x1 -length 300 -from 0 -to 255 -label X
scale .x2 -length 300 -from 0 -to 255 -label Y
scale .x3 -length 300 -from 0 -to 999 -label Ax
scale .x4 -length 300 -from 0 -to 999 -label Ay
scale .x5 -length 300 -from 0 -to 999 -label Az
label .bc -text "  C   " -bg lightblue
label .bz -text "  Z   " -bg lightblue
text .cfg

grid .port -columnspan 7 -sticky w
grid .version -columnspan 7 -sticky w
grid .current -columnspan 7 -sticky w
grid .line -columnspan 7 -sticky w
grid .x3 .x4 .x5 .x1 .x2 .bz .bc
grid .cfg -columnspan 7
