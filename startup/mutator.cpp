#include <dyninst/BPatch.h>
#include <dyninst/BPatch_object.h>
#include <dyninst/BPatch_point.h>
#include <dyninst/BPatch_function.h>
#include <vector>
#include <cstdlib>
#include <time.h>

#define NR_FUNCS 10

double accum;
struct timespec ts_start, ts_end;

void tic(){
    clock_gettime(CLOCK_MONOTONIC, &ts_start);
}

void toc(){
    clock_gettime(CLOCK_MONOTONIC, &ts_end);
    accum = (ts_end.tv_sec - ts_start.tv_sec) + (double)(ts_end.tv_nsec - ts_start.tv_nsec)/1e9;
    FILE *fp;
    fp = fopen("results/instr_cost.dat", "a+");
    if (fp == NULL) {
        fprintf(stderr, "Can't open result file\n");
        exit(1);
    }
    fprintf(fp, "%f\n", accum);
}

int main (int argc, const char* argv[]) {
    tic();
    BPatch bpatch;

    // argv[2] is mutatee's file name, will be mutatee's argv[0]
    BPatch_process *proc = bpatch.processCreate(argv[2], argv + 2);

    // Options to tune performance
    char *s;
    if ((s = getenv("SET_TRAMP_RECURSIVE")) && (strcmp(s, "true") == 0))
        bpatch.setTrampRecursive(true);
    if ((s = getenv("SET_SAVE_FPR")) && (strcmp(s, "false") == 0))
        bpatch.setSaveFPR(false);

    BPatch_object *ipa = proc->loadLibrary(argv[1]);
    BPatch_image *image = proc->getImage();

    std::vector<BPatch_function *> tracepoints, probes;
    image->findFunction("do_stuff_*", tracepoints);
    //BPatch_function *tracepoint = tracepoints[0];
    image->findFunction("tpint_*", probes);
    // BPatch_function *probe = probes[0];
    BPatch_variableExpr* v = image->findVariable("var");
    std::vector<BPatch_snippet*> args;
    BPatch_snippet *var_expr = v;
    args.push_back(var_expr);

    // insert individual tracepoint functions in separate target functions
    for (int i = 0; i<NR_FUNCS; i+=1){
        BPatch_funcCallExpr call_probe(*(probes[i]), args);
        proc->insertSnippet(call_probe, (tracepoints[i]->findPoint(BPatch_exit))[0]);
        // printf("Instrumented do_stuff_%d\n", i);
    }
    proc->detach(true);
    /*
    proc->continueExecution();
    while (!proc->isTerminated()) {
        bpatch.waitForStatusChange();
    }*/
    toc();
    return 0;
}
