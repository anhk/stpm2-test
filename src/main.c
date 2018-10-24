
#include <stdio.h>
#include <stdlib.h>

#include <tss2/tss2_common.h>
#include <tss2/tss2_sys.h>
#include <tss2/tss2_tcti_device.h>

TSS2_SYS_CONTEXT *initSysCtx(TSS2_TCTI_CONTEXT * tctiContext)
{
    TSS2_RC rc;
    int contextSize;
    contextSize = Tss2_Sys_GetContextSize(0);
    printf("sysContextSize: %u\n", contextSize);

    TSS2_SYS_CONTEXT *sysContext;
    if ((sysContext = (TSS2_SYS_CONTEXT *) malloc(contextSize)) == NULL) {
        return NULL;
    }

    printf("sysContext: %p\n", sysContext);

    rc = Tss2_Sys_Initialize(sysContext, contextSize, tctiContext, NULL);
    if (rc != TSS2_RC_SUCCESS) {
        return NULL;
    }

    return sysContext;
}

TSS2_TCTI_CONTEXT *initTctiCtx()
{
    TSS2_RC rc;
    TSS2_TCTI_CONTEXT *tctiContext;
    size_t size;
    char *devPath = "/dev/tpm0";

    rc = Tss2_Tcti_Device_Init(NULL, &size, NULL);
    if (rc != TSS2_RC_SUCCESS) {
        return NULL;
    }

    if ((tctiContext = malloc(size)) == NULL) {
        return NULL;
    }

    rc = Tss2_Tcti_Device_Init(tctiContext, &size, devPath);
    if (rc != TSS2_RC_SUCCESS) {
        return NULL;
    }

    return tctiContext;
}

int main(int argc, char **argv)
{
    TSS2_TCTI_CONTEXT *tctiContext;
    TSS2_SYS_CONTEXT *sysContext;

    if ((tctiContext = initTctiCtx()) == NULL) {
        printf("Error.");
        return -1;
    }

    printf("tctiContext: %p\n", tctiContext);


    if ((sysContext = initSysCtx(tctiContext)) == NULL) {
        printf("Error.");
        return -1;
    }
    return 0;
}
