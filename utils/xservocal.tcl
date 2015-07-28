
proc calc {} {
    global lmid rmid lspan rspan lrange rrange
    if {[llength $lmid] == 0} {set lmid 1500}
    if {[llength $rmid] == 0} {set rmid 1500}
    if {[llength $lspan] == 0} {set lspan 500}
    if {[llength $rspan] == 0} {set rspan 500}
    set lrange [expr $lmid-$lspan]/$lmid/[expr $lmid+$lspan]
    set rrange [expr $rmid-$rspan]/$rmid/[expr $rmid+$rspan]
}


label .xtop -text "ArrBot Calibrator"
label .junk1
label .xleft  -text left
label .xright  -text right

label .xmid  -text midpoint:
label .xspan -text span:

set lmid 1500
set lspan 500
set rmid 1500
set rspan 500

entry .lmid -textvariable lmid
entry .lspan -textvariable lspan
entry .rmid -textvariable rmid
entry .rspan -textvariable rspan

label .lrange -textvariable lrange
label .rrange -textvariable rrange

grid .xtop -columnspan 3
grid .junk1
grid x .xleft .xright -sticky snew
grid .xmid .lmid  .rmid -sticky snew
grid .xspan .lspan  .rspan -sticky snew
grid x .lrange .rrange -sticky snew

frame .cmds
button .cmds.read -text read
button .cmds.write -text write
button .cmds.init -text init
grid .cmds -columnspan 3
grid .cmds.read .cmds.write .cmds.init

foreach i {lmid rmid lspan rspan} {
    bind .$i <FocusOut> calc
    bind .$i <KeyPress-Up> "incr $i; calc; break"
    bind .$i <KeyPress-Down> "incr $i -1; calc; break"
}
calc
