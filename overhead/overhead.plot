# This generates plots for multicore performance of UST+Dyninst vs SystemTap+Dyninst
# Its also has a graph within a graph to enhance results of 1 to 8 thread tests

set terminal svg dynamic enhanced mousing butt solid 
set output 'plots/merged-overhead.svg'

set multiplot

set border linewidth 2

#set boxwidth 2.00 absolute
set style fill   solid 1.00 border lt -1

set style line 1 lt 1 lc rgb "#84c366" lw 2
set style line 2 lt 1 lc rgb "#cb1f1f" lw 2
set style line 3 lt 1 lc rgb "#17cef6" lw 2

set key inside left top vertical Right noreverse noenhanced autotitles nobox
set style histogram clustered gap 1 title  offset character 0, 0, 0
set datafile missing '-'
set style data histogram
set xtics border in scale 0,0 nomirror offset character 0, 0, 0 autojustify
set xtics  norangelimit
set xtics   ()
set title font 'Arial Bold,16' "Overhead analysis of Dyninst and kaji based dynamic \ntracing with increasing workload" 
set logscale y

set key font "Arial Bold"
set xtics font "Arial Bold,14" 
set ytics font "Arial Bold,14"

set xlabel font 'Arial Bold,14' "Events"
set ylabel font 'Arial Bold,14' "Time log(s)"
set grid ytics
set grid mytics
set bmargin 3
plot 'plots/plot-overhead.prep' using 2:xtic(1) ti col ls 1,  '' u 4 ti col ls 3, '' u 5 ti col ls 2
