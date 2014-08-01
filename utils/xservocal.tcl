label .xtop -text "ArrBot Calibrator"
label .xleft  -text "left"
label .xright  -text "right"

label .xmid  -text "midpoint: "
label .xspan -text "span: "

entry .lmid
entry .lspan
entry .rmid
entry .rspan

grid .xtop -columnspan 3
grid x .xleft .xright -sticky "snew"
grid .xmid .lmid  .rmid -sticky "snew"
grid .xspan .lspan  .rspan -sticky "snew"

frame .cmds
button .cmds.read -text read
button .cmds.write -text write
button .cmds.init -text init
grid .cmds -columnspan 3
grid .cmds.read .cmds.write .cmds.init
