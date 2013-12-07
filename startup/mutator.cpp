#include <dyninst/BPatch.h>
#include <dyninst/BPatch_object.h>
#include <dyninst/BPatch_point.h>
#include <dyninst/BPatch_function.h>
#include <vector>
#include <cstdlib>

#define NR_FUNCS 1000

int main (int argc, const char* argv[]) {
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

    return 0;
}
