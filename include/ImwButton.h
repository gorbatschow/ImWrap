#pragma once
#include "ImwBasicElement.h"

namespace Imw {
class Button : public BasicElement {
public:
  // Constructor
  Button(const std::string &label = {}) : BasicElement(label) {
    _width = 50.0f;
    _height = 0.0f;
  }

  // Destructor
  virtual ~Button() override = default;

  // Handle
  virtual bool handle() override {
    const bool trig = _triggered;
    _triggered = false;
    return trig;
  }

protected:
  // Paint Element
  virtual void paintElement() override {
    const ImVec2 sz{std::isnan(_width) ? 0.f : _width,
                    std::isnan(_height) ? 0.f : _height};
    _triggered = ImGui::Button(_label.c_str(), sz);
  }

  bool _triggered{false};
};
} // namespace Imw
