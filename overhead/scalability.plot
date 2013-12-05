# This generates plots for multicore performance of UST+Dyninst vs SystemTap+Dyninst
# Its also has a graph within a graph to enhance results of 1 to 8 thread tests

set terminal svg dynamic enhanced mousing butt solid 
set output 'plots/merged-scalability.svg'

set multiplot

set border linewidth 2
set boxwidth 1.00 absolute
set style fill   solid 1.00 border lt -1

set style line 1 lt 1 lc rgb "#17cef6" lw 2
set style line 2 lt 1 lc rgb "#cb1f1f" lw 2
set style line 3 lt 1 lc rgb "#84c366" lw 2

set key inside left top vertical Right noreverse noenhanced autotitles nobox
set style histogram clustered gap 1 title  offset character 0, 0, 0
set datafile missing '-'
set style data histogram
set xtics border in scale 0,0 nomirror offset character 0, 0, 0 autojustify
set xtics  norangelimit
set xtics   ()

set title font 'Arial Bold,16' "Multi-core dynamic tracing with Dyninst and Kaji\n with 1M events on a 64 core machine" 

set logscale y
set xlabel font 'Arial Bold,14' "Threads"
set ylabel font 'Aria Bold, 14' "Time (s)"

set key font "Arial Bold"
set xtics font "Arial Bold,14" 
set ytics font "Arial Bold,14" 

set grid ytics lc rgb "#bbbbbb" lw 1 lt 0
set grid mytics lc rgb "#bbbbbb" lw 1 lt 0

plot 'plots/plot-scalability.prep' u 2:xtic(1) ti col ls 1, '' u 4 ti col ls 2, '' u 5 ti col ls 3
