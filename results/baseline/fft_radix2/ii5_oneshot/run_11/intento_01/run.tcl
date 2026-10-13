# Generado por baseline/arnes.py. Mismo part / reloj / flow_target que el
# run.tcl que genera Allo para L4; csim añadido para validar funcionalmente.
open_project proj -reset
open_solution -reset solution1 -flow_target vivado
set_top fft_radix2
add_files kernel.cpp
add_files -tb tb.cpp
add_files -tb vectores.h
set_part {xcu280-fsvh2892-2L-e}
create_clock -period 3.33

if {[catch {csim_design -ldflags {-B/usr/bin/}} msg]} {
  puts "BASELINE_CSIM_ERROR: $msg"
} else {
  puts "BASELINE_CSIM_DONE"
}

if {[catch {csynth_design} msg]} {
  puts "BASELINE_CSYNTH_ERROR: $msg"
} else {
  puts "BASELINE_CSYNTH_DONE"
}

exit
