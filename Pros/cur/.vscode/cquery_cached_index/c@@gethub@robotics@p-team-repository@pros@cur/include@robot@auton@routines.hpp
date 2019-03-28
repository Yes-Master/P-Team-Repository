#ifndef ROUTINES_HPP
#define ROUTINES_HPP
namespace Auton{
  namespace Routines{
    void doubleShotFront(void* test);
    namespace Red{
      namespace Front{
        void midBoth();
        void midHold();
        void midTop();
        void midBottom();
      }
      namespace Back{
        void farPark();
        void farCap();
        void farAll();
        void midCap();
      }
    }
    namespace Blue{
      namespace Front{
        void midBoth();
        void midHold();
        void midTop();
        void midBottom();
      }
      namespace Back{
        void farPark();
        void farCap();
        void farAll();
        void midCap();
      }
    }
    void skills();
    void testR();
    void testB();
    void defaultSelection();
  }
}
#endif /* end of include guard: ROUTINES_HPP */
