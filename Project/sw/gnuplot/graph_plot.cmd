# Window-setup
set title "Test graph layout"         # Set title
set xrange [-145:85];                 # Define x-coord printin' range
set yrange [-145:85];                 # Define y-coord printin' range
unset xtics                           # Hide x-axis ticks
unset ytics                           # Hide y-axis ticks

# PLOT TEST NODES & ARCHS FROM FILES
plot \
  'gnuplot/archs.dat' using 1:2       with lines lt rgb "dark-violet" notitle, \
  'gnuplot/costs.dat' using 1:2:3     with labels tc rgb "blue" offset (0,0) font 'Arial Bold' notitle, \
  'gnuplot/nodes.dat' using 1:2:(9.2) with circles fill solid lc rgb "black" notitle, \
  'gnuplot/nodes.dat' using 1:2:3     with labels tc rgb "white" offset (0,0) font 'Arial Bold' notitle
