#pragma once
#include "ImWrapElementWatcher.h"
#include "ImWrapIElement.h"
#include <cmath>
#include <imgui.h>
#include <string>

namespace ImWrap {
class BasicElement : public IElement {
public:
  // Constructor
  BasicElement(const std::string &label = {})
      : _label{label}, _elementId{ElementWatcher::instance().makeElementId()} {
    ElementWatcher::instance().addElement(this);
  }

  // Destructor
  virtual ~BasicElement() override {
    ElementWatcher::instance().removeElement(this);
  }

  // Element Id
  virtual int elementId() const override final { return _elementId; }

  std::string elementIdStr() const override final {
    auto labelId{_label};
    std::erase_if(labelId, [](const char c) {
      return c == ' ' || c == '[' || c == ']' || c == '/' || c == '\\'
             || c == '{' || c == '}' || c == '(' || c == ')';
    });

    return "imwrap_" + labelId + std::to_string(_elementId);
  }

  // Load State
  virtual void loadStateFromFile() override {
    ElementWatcher::instance().loadElementState(this);
  }

  virtual void saveStateToFile() override {
    ElementWatcher::instance().saveElementState(this);
  }

  // Paint
  virtual void paint() override final {
    if (!_visible) {
      return;
    }

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
  virtual bool handle() const override {
    const auto triggered{_triggered};
    _triggered = false;
    return triggered;
  }

  // Trigger
  virtual void trigger() const override { _triggered = true; }

  inline void setVisible(bool value) { _visible = value; }
  inline bool visible() const { return _visible; }

  inline void setEnabled(bool value) { _enabled = value; }
  inline bool enabled() const { return _enabled; }

  inline void setWidth(float w) { _width = w; }
  inline float width() const { return _width; }

  inline void setHeight(float h) { _height = h; }
  inline float height() const { return _height; }

  inline void setVerical(bool isVertical) { _isVertical = true; }
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

  mutable bool _triggered{false};
  bool _enabled{true};
  bool _visible{true};
  float _width{std::numeric_limits<float>::quiet_NaN()};
  float _height{std::numeric_limits<float>::quiet_NaN()};
  bool _isVertical{false};
  std::string _label{"##"};
  bool _sameLine{};
  float _sameLineOffset{};
  float _sameLineSpacing{-1.0f};
  std::string _textFormat{};
  std::string _placeHolder{};
  int _elementId{};
};
} // namespace ImWrap
