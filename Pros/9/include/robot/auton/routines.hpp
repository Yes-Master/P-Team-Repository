#ifndef ROUTINES_HPP
#define ROUTINES_HPP
namespace Auton{
  namespace Routines{
    void doubleShotFront(void* test);
    void defaultSelection();
    void skills();
    namespace Red{
      namespace Front{
        void midBoth();
        void midHold();
        void midTop();
        void midBottom();
      }
    }
    namespace Blue{
      namespace Front{
        void midBoth();
        void midHold();
        void midTop();
        void midBottom();
      }
    }
  }
}
#endif /* end of include guard: ROUTINES_HPP */
