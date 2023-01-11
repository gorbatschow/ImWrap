#pragma once
#include "ImwMultiValueElement.h"
#include <vector>

namespace Imw {
template <class T>
class ComboBox : public MultiValueElement<std::pair<T, std::string>> {
  using Parent = MultiValueElement<std::pair<T, std::string>>;

public:
  // Constructor
  ComboBox(const std::string &label = {}) : Parent(0, label) {}

  // Constructor
  ComboBox(const std::string &label,
           const std::vector<std::pair<T, std::string>> &values)
      : Parent(values.size(), label), Parent::_valueList(values) {}

  // Destructor
  virtual ~ComboBox() override = default;

  inline const T &operator()() { return Parent::currentValue().first; }

protected:
  // Paint Element
  virtual void paintElement() override {

    Parent::_currIndex = Parent::_valueList.empty() ? -1 : Parent::_currIndex;
    if (Parent::_currIndex < 0) {
      // Value list IS empty
      if (ImGui::BeginCombo(Parent::_label.c_str(),
                            Parent::_placeHolder.c_str())) {
        ImGui::EndCombo();
      }
    } else {
      // Value list is NOT empty
      if (ImGui::BeginCombo(
              Parent::_label.c_str(),
              Parent::_valueList.at(Parent::_currIndex).second.c_str())) {
        for (size_t i = 0; i != Parent::_valueList.size(); ++i) {
          if (ImGui::Selectable(Parent::_valueList[i].second.c_str(),
                                i == Parent::_currIndex)) {
            Parent::_currIndex = i;
            Parent::_changed = true;
          }
        }
        ImGui::EndCombo();
      }
    }
  }
};
} // namespace Imw
