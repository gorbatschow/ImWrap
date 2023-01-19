#pragma once
#include "ImwIElement.h"
#include <algorithm>
#include <memory>
#include <vector>

namespace Imw {
class ElementWatcher {
  // <Singleton>
public:
  static ElementWatcher &instance() {
    static ElementWatcher instance;
    return instance;
  }
  ElementWatcher(ElementWatcher const &) = delete;
  void operator=(ElementWatcher const &) = delete;

private:
  ElementWatcher() {}
  // </Singleton>

public:
  // Make Element Id
  inline int makeElementId() { return _elementCounter++; }

  // Add Element
  inline void addElement(IElement *element) { _elements.push_back(element); }

  // Remove Element
  inline void removeElement(IElement *element) {
    std::remove_if(_elements.begin(), _elements.end(),
                   [element](IElement *item) { return element == item; });
  }

  // Load Element State
  inline void loadElementState(const std::string &file = "imwrap.ini") {
    mINI::INIFile iniFile(file);
    mINI::INIStructure ini;
    iniFile.read(ini);
    for (auto &element : _elements) {
      element->loadState(ini);
    }
  }

  // Save Element State
  inline void saveElementState(const std::string &file = "imwrap.ini") {
    mINI::INIFile iniFile(file);
    mINI::INIStructure ini;
    for (auto &element : _elements) {
      element->saveState(ini);
    }
    iniFile.write(ini);
  }

  // Trigger Value Element
  inline void triggerValueElement() {
    for (auto &element : _elements) {
      if (element->isValueElement()) {
        element->trigger();
      }
    }
  }

  // Get Elements
  inline const std::vector<IElement *> &elements() const { return _elements; }

private:
  std::vector<IElement *> _elements;
  int _elementCounter{};
};
} // namespace Imw
