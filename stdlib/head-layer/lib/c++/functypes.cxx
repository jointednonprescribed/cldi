


/* Implementing: cldi-head: functypes.h */
#include <cldi/head/functypes.h>



namespace cldi
{
    /* class subroutine */
    subroutine::subroutine():
        function<void>(NULL)
    {}
    subroutine::subroutine(void (*func)()):
        function<void>(func)
    {}
    subroutine::subroutine(function<void> callable):
        function<void>(callable.call)
    {}
}


