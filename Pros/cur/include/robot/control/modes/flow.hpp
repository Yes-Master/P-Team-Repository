#pragma once
namespace flow {
  // vars
  enum class Modes { FLAG, CAPS, DEBUG, NONE };
  // vars FUNCTIONS
  Modes get_mode();
  void set_mode(Modes m);
  // methods
  void init();
  void user();
}  // namespace flow