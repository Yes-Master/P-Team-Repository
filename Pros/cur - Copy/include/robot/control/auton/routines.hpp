#ifndef ROUTINES_HPP
#define ROUTINES_HPP
namespace auton{
  namespace routines{
    void doubleShotFront(void* test);
    namespace red{
      namespace front{
        void midBoth();
        void midHold();
        void midTop();
        void midBottom();
        void cloFar();
      }
      namespace back{
        void farPark();
        void farCap();
        void farAll();
        void midCap();
      }
    }
    namespace blue{
      namespace front{
        void midBoth();
        void midHold();
        void midTop();
        void midBottom();
        void cloFar();
      }
      namespace back{
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
