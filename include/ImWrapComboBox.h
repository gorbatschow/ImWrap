#pragma once
#include "ImWrapMultiValueElement.h"
#include "ImWrapNamedValue.h"
#include <vector>

namespace ImWrap {
template <typename T> class ComboBox : public MultiValueElement<NamedValue<T>> {
  using Base = MultiValueElement<NamedValue<T>>;

public:
  // Constructor
  ComboBox(const std::string &label = {}) : Base(label) {}

  // Constructor
  ComboBox(const std::string &label,
           const std::vector<std::pair<T, std::string>> &values)
      : Base(values.size(), label), Base::_valueList(values) {}

  // Destructor
  virtual ~ComboBox() override = default;

  // Set Current Name
  virtual void setCurrentName(const std::string &name) override {
    const auto it{std::find_if(
        Base::_valueList.begin(), Base::_valueList.end(),
        [&name](const NamedValue<T> &value) { return value.name() == name; })};
    if (it != Base::_valueList.end()) {
      Base::setCurrentIndex(std::distance(Base::_valueList.begin(), it));
    }
  }

  // Load State
  virtual void loadState(const mINI::INIStructure &ini) override {
    static constexpr auto key{"name"};
    if (!ini.get(Base::elementIdStr()).has(key)) {
      return;
    }
    setCurrentName({ini.get(Base::elementIdStr()).get(key)});
  }

  // Save State
  virtual void saveState(mINI::INIStructure &ini) const override {
    static constexpr auto key{"name"};
    if (Base::isCurrentValid()) {
      ini[Base::elementIdStr()][key] = Base::currentValue().name();
    }
  }

  // Get Value
  inline const T &operator()() { return Base::currentValue(); }

  // Set Value by Name

protected:
  // Paint Element
  virtual void paintElement() override {
    if (Base::_valueList.empty()) {
      // Value list IS empty
      if (ImGui::BeginCombo(Base::_label.c_str(), Base::_placeHolder.c_str())) {
        ImGui::EndCombo();
      }
    } else {
      // Value list is NOT empty
      const auto namePtr{Base::_currIndex >= 0
                             ? Base::_valueList.at(Base::_currIndex).namePtr()
                             : Base::_placeHolder.c_str()};
      if (ImGui::BeginCombo(Base::_label.c_str(), namePtr)) {
        for (size_t i = 0; i != Base::_valueList.size(); ++i) {
          if (ImGui::Selectable(Base::_valueList.at(i).namePtr(),
                                i == Base::_currIndex)) {
            Base::_currIndex = i;
            Base::trigger();
          }
        }
        ImGui::EndCombo();
      }
    }
  }
};
} // namespace ImWrap
