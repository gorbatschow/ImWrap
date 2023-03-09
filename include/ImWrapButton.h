#pragma once
#include "ImWrapBasicElement.h"

namespace ImWrap {
class Button : public BasicElement {
public:
  // Constructor
  Button(const std::string &label = {}) : BasicElement(label) {
    _width = 50.0f;
    _height = 0.0f;
  }

  // Destructor
  virtual ~Button() override = default;

  // Is Button
  virtual bool isButtonElement() const override final { return true; }

protected:
  // Paint Element
  virtual void paintElement() override {
    const ImVec2 sz{std::isnan(_width) ? 0.f : _width,
                    std::isnan(_height) ? 0.f : _height};
    if (ImGui::Button(_label.c_str(), sz)) {
      trigger();
    }
  }
};
} // namespace ImWrap
