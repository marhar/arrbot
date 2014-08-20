set port /dev/cu.usbserial-A8004yjB
set baud 115200

proc doread {fd} {
    if {[gets $fd s] < 0} {
        puts "eof on read"
        exit 0
    }
    puts $s
}


set s [open $port r+]
fconfigure $s -mode $baud,n,8,1 -translation auto \
    -buffering none -buffersize 12
fileevent $s readable "doread $s"

