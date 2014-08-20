set port /dev/cu.usbserial-A8004yjB
set baud 115200

proc doread {fd} {
    # 0  1   2   3   4   5   6 7
    # n  130 132 306 539 580 0 0

    global line

    if {[gets $fd line] < 0} {
        puts "eof on read"
        exit 0
    }
    #puts line=[llength $line],$line
    if {[llength $line] != 8} {
        return
    }
    foreach i {1 2 3 4 5} {
        .x$i set [lindex $line $i]
    }
    set bz [lindex $line 6]
    set bc [lindex $line 7]
    if {$bz} { .bz configure -bg blue } else { .bz configure -bg lightblue }
    if {$bc} { .bc configure -bg blue } else { .bc configure -bg lightblue }
    update
}

proc bgerror {msg} {
    global errorInfo
    close $::ser
    puts "I got an error in an event: $msg"
    puts "The stack trace was this:\n$errorInfo"
}


set ::ser [open $port r+]
fconfigure $::ser -mode $baud,n,8,1
fileevent $::ser readable "doread $::ser"

label .port -textvariable ::port
label .line -textvariable ::line
scale .x1 -length 300 -from 0 -to 255 -label X
scale .x2 -length 300 -from 0 -to 255 -label Y
scale .x3 -length 300 -from 0 -to 999 -label Ax
scale .x4 -length 300 -from 0 -to 999 -label Ay
scale .x5 -length 300 -from 0 -to 999 -label Az
label .bc -text "  C   " -bg lightblue
label .bz -text "  Z   " -bg lightblue

grid .port -columnspan 7
grid .line -columnspan 7
grid .x3 .x4 .x5 .x1 .x2 .bz .bc
