#pragma once
#include "ImwIElement.h"
#include <cmath>
#include <imgui.h>
#include <string>

namespace Imw {
class BasicElement : public IElement {
public:
  // Constructor
  BasicElement(const std::string &label = {}) : _label{label} {}

  // Destructor
  virtual ~BasicElement() override = default;

  // Paint
  virtual void paint() override {
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

  // Handle
  virtual bool handle() override { return false; }

  inline void setWidth(float w) { _width = w; }
  inline float width() const { return _width; }

  inline void setHeight(float h) { _height = h; }
  inline float height() const { return _height; }

  inline void setVerical(bool isVertical) {}
  inline bool isVertical() { return _isVertical; }

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

  void setPlaceHolder(const std::string &placeHolder) {
    _placeHolder = placeHolder;
  }
  const std::string &placeHodler() const { return _placeHolder; }

protected:
  virtual void paintElement() {}

  float _width{std::numeric_limits<float>::quiet_NaN()};
  float _height{std::numeric_limits<float>::quiet_NaN()};
  bool _isVertical{false};
  std::string _label{"##"};
  bool _sameLine{};
  float _sameLineOffset{};
  float _sameLineSpacing{-1.0f};
  std::string _textFormat{};
  std::string _placeHolder{};
};
} // namespace Imw
