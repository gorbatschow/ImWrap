#pragma once
#include <cmath>
#include <imgui.h>
#include <string>

namespace Imw {
class BasicElement {
public:
  BasicElement(const std::string &label = {}) : _label{label} {}

  virtual ~BasicElement() = default;

  virtual void paint() {
    ImGui::PushID(this);
    if (_sameLine) {
      ImGui::SameLine(_sameLineOffset, _sameLineSpacing);
    }
    if (!std::isnan(_width)) {
      ImGui::PushItemWidth(_width);
    }
    paintElement();
    if (!std::isnan(_width)) {
      ImGui::PopItemWidth();
    }
    ImGui::PopID();
  }

  virtual bool handle() { return false; }

  inline void setWidth(float w) { _width = w; }
  inline float width() const { return _width; }

  inline void setLabel(const std::string &label) { _label = label; }
  inline const std::string &label() const { return _label; }

  inline void setSameLine(bool sameLine) { _sameLine = sameLine; }
  inline bool sameLine() const { return _sameLine; }

  inline void setSameLineOffset(float x) { _sameLineOffset = x; }
  inline float sameLineOffet() const { return _sameLineOffset; }

  inline void setSameLineSpacing(float s) { _sameLineSpacing = s; }
  inline float sameLineSpacing() const { return _sameLineSpacing; }

  void setTextFormat(const std::string &format) { _textFormat = format; }
  const std::string &textFormat() const { return _textFormat; }

protected:
  virtual void paintElement() {}

  float _width{std::numeric_limits<float>::quiet_NaN()};
  std::string _label{"##"};
  bool _sameLine{};
  float _sameLineOffset{};
  float _sameLineSpacing{-1.0f};
  std::string _textFormat{};
};
} // namespace Imw
