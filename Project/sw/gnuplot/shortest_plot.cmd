# Window-setup
set title "Test graph layout with shortest-path"  # Set title
set size square                                   # Maintain the same scale on x and y axes
set xrange [-145:85];                             # Define x-coord printin' range
set yrange [-145:85];                             # Define y-coord printin' range
unset xtics                                       # Hide x-axis ticks
unset ytics                                       # Hide y-axis ticks

# PLOT TEST NODES & ARCHS FROM FILES WITH SHORTEST-PATH FROM SOURCE TO DESTINATION NODES
plot \
  'gnuplot/archs.dat' using 1:2                   with lines lt rgb "gray" notitle, \
  'gnuplot/costs.dat' using 1:2:3                 with labels tc rgb "light-blue" offset (0,0) font 'Arial Bold' notitle, \
  'gnuplot/nodes.dat' using 1:2:(9.2)             with circles fill solid lc rgb "gray" notitle, \
  'gnuplot/nodes.dat' using 1:2:3                 with labels tc rgb "white" offset (0,0) font 'Arial' notitle, \
  'gnuplot/shortest_archs.dat' using 1:2          with lines lt rgb "dark-green" notitle, \
  'gnuplot/shortest_costs.dat' using 1:2:3        with labels tc rgb "blue" offset (0,0) font 'Arial Bold' notitle, \
  'gnuplot/shortest_nodes.dat' using 1:2:(9.2)    with circles fill solid lc rgb "forest-green" notitle, \
  'gnuplot/shortest_nodes.dat' using 1:2:3        with labels tc rgb "white" offset (0,0) font 'Arial Bold' notitle, \
  'gnuplot/src_dest_nodes.dat' using 1:2:(9.2)    with circles fill solid lc rgb "dark-violet" notitle, \
  'gnuplot/src_dest_nodes.dat' using 1:2:3        with labels tc rgb "white" offset (0,0) font 'Arial Bold' notitle
