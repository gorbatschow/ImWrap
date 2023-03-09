#pragma once
#include "ImWrapIElement.h"
#include <algorithm>
#include <memory>
#include <vector>

namespace ImWrap {
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
  ElementWatcher() { setIniFileName("imwrap.ini"); }
  // </Singleton>

public:
  // Ini File Name
  inline void setIniFileName(const std::string &fname) {
    _iniFileName = fname;
    mINI::INIFile iniFile(_iniFileName);
    iniFile.read(_ini);
  }

  // File Name
  inline const std::string &iniFileName() const { return _iniFileName; }

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
  inline void loadElementState(IElement *element) { element->loadState(_ini); }

  // Load Element State
  inline void loadElementState(const std::vector<IElement *> &elementList) {
    for (auto &element : elementList) {
      element->loadState(_ini);
    }
  }

  // Load Element State
  inline void loadElementState() { loadElementState(_elements); }

  // Save Element State
  inline void saveElementState(IElement *element) {
    element->saveState(_ini);
    mINI::INIFile iniFile(_iniFileName);
    iniFile.write(_ini);
  }

  // Save Element State
  inline void saveElementState() {
    mINI::INIFile iniFile(_iniFileName);
    for (auto &element : _elements) {
      element->saveState(_ini);
    }
    iniFile.write(_ini);
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
  mINI::INIStructure _ini;
  std::string _iniFileName;
};
} // namespace ImWrap
