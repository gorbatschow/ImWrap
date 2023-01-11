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
    if (std::isnan(_width)) {
      _triggered = ImGui::Button(_label.c_str());
    } else {
      _triggered = ImGui::Button(_label.c_str(), {_width, _height});
    }
  }

  bool _triggered{false};
};
} // namespace Imw
