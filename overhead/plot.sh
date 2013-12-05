#!/bin/sh

OVERHEAD_PLOT_FILE="plots/plot-overhead.prep"
SCALABILITY_PLOT_FILE="plots/plot-scalability.prep"
STARTUP_PLOT_FILE="plots/plot-startup.prep"

PLOT_SCALABILITY="scalability.plot"
PLOT_OVERHEAD="overhead.plot"
PLOT_STARTUP="startup.plot"

RESULTS_DIR="results"

if [ $# -ne 1 ] ; then
        echo "Usage : $0 [overhead | scalability | startup]"
        exit 3
fi

function overhead {

	echo "Preprocessing.."
	echo ''	
	#Intialize overhead histogram
	rm -f plots/plot-overhead.prep
	echo "#Overhead results" 2>&1 | tee -a $OVERHEAD_PLOT_FILE
	echo "#" 2>&1 | tee -a $OVERHEAD_PLOT_FILE
	echo -e "Events\tClean\tStatic\tDynamic(Dyninst)\tDynamic(Kaji)" 2>&1 | tee -a $OVERHEAD_PLOT_FILE
	#Merge results
	sort -n $RESULTS_DIR/* 2>&1 | tee -a $OVERHEAD_PLOT_FILE
	echo ''

	#Plotting commences..
	echo "Plotting overhead graphs.."
	gnuplot $PLOT_OVERHEAD
}

function scalability {
	
	echo "Preprocessing.."
	echo ''	
	#Intialize scalability histogram
	rm -f plots/plot-scalability.prep
	echo "#Scalability results" 2>&1 | tee -a $SCALABILITY_PLOT_FILE
	echo "#" 2>&1 | tee -a $SCALABILITY_PLOT_FILE
	echo -e "Threads\tClean\tStatic\tDynamic(Dyninst)\tDynamic(Kaji)" 2>&1 | tee -a $SCALABILITY_PLOT_FILE
	#Merge results
	sort -n $RESULTS_DIR/* 2>&1 | tee -a $SCALABILITY_PLOT_FILE
	echo ''

	#Plotting commences..
	echo "Plotting scalability graphs.."
	gnuplot $PLOT_SCALABILITY

}

function startup {
	
	echo "Preprocessing.."
	echo ''	
	#Intialize startup histogram
	rm -f plots/plot-startup.prep
	echo "#Startup results" 2>&1 | tee -a $STARTUP_PLOT_FILE
	echo "#" 2>&1 | tee -a $STARTUP_PLOT_FILE
	echo -e "Threads\tClean\tStatic\tDynamic(Dyninst)\tDynamic(Kaji)" 2>&1 | tee -a $STARTUP_PLOT_FILE
	#Merge results
	# sort $RESULTS_DIR/* 2>&1 | tee -a $STARTUP_PLOT_FILE
	echo ''

}

# Parse plot types
case "$1" in
"overhead")
    overhead
    ;;
"scalability")
    scalability
    ;;
"startup")
	startup
    ;;
*)
    echo "Invalid option"
    exit 3
    ;;
esac