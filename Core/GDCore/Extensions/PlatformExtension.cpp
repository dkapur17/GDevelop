/*
 * GDevelop Core
 * Copyright 2008-2016 Florian Rival (Florian.Rival@gmail.com). All rights
 * reserved. This project is released under the MIT License.
 */
#include "GDCore/Extensions/PlatformExtension.h"

#include <algorithm>

#include "GDCore/Events/Event.h"
#include "GDCore/Extensions/Metadata/BehaviorMetadata.h"
#include "GDCore/Extensions/Metadata/DependencyMetadata.h"
#include "GDCore/Extensions/Metadata/EventMetadata.h"
#include "GDCore/Extensions/Metadata/ExpressionMetadata.h"
#include "GDCore/Extensions/Metadata/InstructionMetadata.h"
#include "GDCore/Extensions/Metadata/ObjectMetadata.h"
#include "GDCore/Extensions/Platform.h"
#include "GDCore/IDE/PlatformManager.h"
#include "GDCore/Project/Behavior.h"
#include "GDCore/Project/BehaviorsSharedData.h"

namespace gd {

#if defined(GD_IDE_ONLY)
std::map<gd::String, gd::InstructionMetadata>
    PlatformExtension::badConditionsMetadata;
std::map<gd::String, gd::InstructionMetadata>
    PlatformExtension::badActionsMetadata;
std::map<gd::String, gd::ExpressionMetadata>
    PlatformExtension::badExpressionsMetadata;
std::map<gd::String, gd::ExpressionMetadata>
    PlatformExtension::badStrExpressionsMetadata;
#endif

gd::InstructionMetadata& PlatformExtension::AddCondition(
    const gd::String& name,
    const gd::String& fullname,
    const gd::String& description,
    const gd::String& sentence,
    const gd::String& group,
    const gd::String& icon,
    const gd::String& smallicon) {
#if defined(GD_IDE_ONLY)
  gd::String nameWithNamespace =
      GetNameSpace().empty() ? name : GetNameSpace() + name;
  conditionsInfos[nameWithNamespace] = InstructionMetadata(GetNameSpace(),
                                                           nameWithNamespace,
                                                           fullname,
                                                           description,
                                                           sentence,
                                                           group,
                                                           icon,
                                                           smallicon)
                                           .SetHelpPath(GetHelpPath());
  return conditionsInfos[nameWithNamespace];
#endif
}

gd::InstructionMetadata& PlatformExtension::AddAction(
    const gd::String& name,
    const gd::String& fullname,
    const gd::String& description,
    const gd::String& sentence,
    const gd::String& group,
    const gd::String& icon,
    const gd::String& smallicon) {
#if defined(GD_IDE_ONLY)
  gd::String nameWithNamespace =
      GetNameSpace().empty() ? name : GetNameSpace() + name;
  actionsInfos[nameWithNamespace] = InstructionMetadata(GetNameSpace(),
                                                        nameWithNamespace,
                                                        fullname,
                                                        description,
                                                        sentence,
                                                        group,
                                                        icon,
                                                        smallicon)
                                        .SetHelpPath(GetHelpPath());
  return actionsInfos[nameWithNamespace];
#endif
}

gd::ExpressionMetadata& PlatformExtension::AddExpression(
    const gd::String& name,
    const gd::String& fullname,
    const gd::String& description,
    const gd::String& group,
    const gd::String& smallicon) {
#if defined(GD_IDE_ONLY)
  gd::String nameWithNamespace =
      GetNameSpace().empty() ? name : GetNameSpace() + name;
  expressionsInfos[nameWithNamespace] = ExpressionMetadata(GetNameSpace(),
                                                           nameWithNamespace,
                                                           fullname,
                                                           description,
                                                           group,
                                                           smallicon)
                                            .SetHelpPath(GetHelpPath());
  return expressionsInfos[nameWithNamespace];
#endif
}

gd::ExpressionMetadata& PlatformExtension::AddStrExpression(
    const gd::String& name,
    const gd::String& fullname,
    const gd::String& description,
    const gd::String& group,
    const gd::String& smallicon) {
#if defined(GD_IDE_ONLY)
  gd::String nameWithNamespace =
      GetNameSpace().empty() ? name : GetNameSpace() + name;
  strExpressionsInfos[nameWithNamespace] = ExpressionMetadata(GetNameSpace(),
                                                              nameWithNamespace,
                                                              fullname,
                                                              description,
                                                              group,
                                                              smallicon)
                                               .SetHelpPath(GetHelpPath());
  return strExpressionsInfos[nameWithNamespace];
#endif
}

#if defined(GD_IDE_ONLY)
gd::DependencyMetadata& PlatformExtension::AddDependency() {
  extensionDependenciesMetadata.push_back(DependencyMetadata());
  return extensionDependenciesMetadata.back();
}
#endif

gd::ObjectMetadata& PlatformExtension::AddObject(
    const gd::String& name,
    const gd::String& fullname,
    const gd::String& description,
    const gd::String& icon24x24,
    std::shared_ptr<gd::Object> instance) {
  gd::String nameWithNamespace =
      GetNameSpace().empty() ? name : GetNameSpace() + name;
  objectsInfos[nameWithNamespace] = ObjectMetadata(GetNameSpace(),
                                                   nameWithNamespace,
                                                   fullname,
                                                   description,
                                                   icon24x24,
                                                   instance)
                                        .SetHelpPath(GetHelpPath());

  return objectsInfos[nameWithNamespace];
}

gd::BehaviorMetadata& PlatformExtension::AddBehavior(
    const gd::String& name,
    const gd::String& fullname,
    const gd::String& defaultName,
    const gd::String& description,
    const gd::String& group,
    const gd::String& icon24x24,
    const gd::String& className,
    std::shared_ptr<gd::Behavior> instance,
    std::shared_ptr<gd::BehaviorsSharedData> sharedDatasInstance) {
  gd::String nameWithNamespace =
      GetNameSpace().empty() ? name : GetNameSpace() + name;
  behaviorsInfo[nameWithNamespace] = BehaviorMetadata(GetNameSpace(),
                                                      nameWithNamespace,
                                                      fullname,
                                                      defaultName,
                                                      description,
                                                      group,
                                                      icon24x24,
                                                      className,
                                                      instance,
                                                      sharedDatasInstance)
                                         .SetHelpPath(GetHelpPath());
  return behaviorsInfo[nameWithNamespace];
}

gd::EffectMetadata& PlatformExtension::AddEffect(const gd::String& name) {
  gd::String nameWithNamespace =
      GetNameSpace().empty() ? name : GetNameSpace() + name;
  effectsMetadata[nameWithNamespace] = EffectMetadata(nameWithNamespace);
  return effectsMetadata[nameWithNamespace];
}

gd::EventMetadata& PlatformExtension::AddEvent(
    const gd::String& name_,
    const gd::String& fullname_,
    const gd::String& description_,
    const gd::String& group_,
    const gd::String& smallicon_,
    std::shared_ptr<gd::BaseEvent> instance_) {
#if defined(GD_IDE_ONLY)
  gd::String nameWithNamespace =
      GetNameSpace().empty() ? name_ : GetNameSpace() + name_;
  eventsInfos[nameWithNamespace] = gd::EventMetadata(nameWithNamespace,
                                                     fullname_,
                                                     description_,
                                                     group_,
                                                     smallicon_,
                                                     instance_);
  return eventsInfos[nameWithNamespace];
#endif
}

PlatformExtension& PlatformExtension::SetExtensionInformation(
    const gd::String& name_,
    const gd::String& fullname_,
    const gd::String& description_,
    const gd::String& author_,
    const gd::String& license_) {
  name = name_;
  fullname = fullname_;
  informations = description_;
  author = author_;
  license = license_;
  SetNameSpace(name_);
  return *this;
}

std::vector<gd::String> PlatformExtension::GetExtensionObjectsTypes() const {
  std::vector<gd::String> objects;

  std::map<gd::String, gd::ObjectMetadata>::const_iterator it;
  for (it = objectsInfos.begin(); it != objectsInfos.end(); ++it)
    objects.push_back(it->first);

  return objects;
}

std::vector<gd::String> PlatformExtension::GetExtensionEffectTypes() const {
  std::vector<gd::String> effectNames;
  for (auto& it : effectsMetadata) effectNames.push_back(it.first);

  return effectNames;
}

gd::ObjectMetadata& PlatformExtension::GetObjectMetadata(
    const gd::String& objectType) {
  if (objectsInfos.find(objectType) != objectsInfos.end())
    return objectsInfos.find(objectType)->second;

  std::cout << "Warning: Object type \"" << objectType
            << "\" not found in an extension!" << std::endl;
  return badObjectMetadata;
}

gd::BehaviorMetadata& PlatformExtension::GetBehaviorMetadata(
    const gd::String& behaviorType) {
  if (behaviorsInfo.find(behaviorType) != behaviorsInfo.end())
    return behaviorsInfo.find(behaviorType)->second;

  std::cout << "Warning: Behavior type \"" << behaviorType
            << "\" not found in an extension!" << std::endl;
  return badBehaviorMetadata;
}

gd::EffectMetadata& PlatformExtension::GetEffectMetadata(
    const gd::String& effectName) {
  if (effectsMetadata.find(effectName) != effectsMetadata.end())
    return effectsMetadata.find(effectName)->second;

  std::cout << "Warning: Effect with name \"" << effectName
            << "\" not found in an extension!" << std::endl;
  return badEffectMetadata;
}

std::vector<gd::String> PlatformExtension::GetBehaviorsTypes() const {
  std::vector<gd::String> behaviors;

  std::map<gd::String, gd::BehaviorMetadata>::const_iterator it;
  for (it = behaviorsInfo.begin(); it != behaviorsInfo.end(); ++it)
    behaviors.push_back(it->first);

  return behaviors;
}

#if defined(GD_IDE_ONLY)
std::map<gd::String, gd::InstructionMetadata>&
PlatformExtension::GetAllActions() {
  return actionsInfos;
}

std::map<gd::String, gd::InstructionMetadata>&
PlatformExtension::GetAllConditions() {
  return conditionsInfos;
}

std::map<gd::String, gd::ExpressionMetadata>&
PlatformExtension::GetAllExpressions() {
  return expressionsInfos;
}

std::map<gd::String, gd::ExpressionMetadata>&
PlatformExtension::GetAllStrExpressions() {
  return strExpressionsInfos;
}

std::vector<gd::DependencyMetadata>& PlatformExtension::GetAllDependencies() {
  return extensionDependenciesMetadata;
}

std::map<gd::String, gd::EventMetadata>& PlatformExtension::GetAllEvents() {
  return eventsInfos;
}
std::map<gd::String, gd::InstructionMetadata>&
PlatformExtension::GetAllActionsForObject(gd::String objectType) {
  if (objectsInfos.find(objectType) != objectsInfos.end())
    return objectsInfos.find(objectType)->second.actionsInfos;

  return badActionsMetadata;
}

std::map<gd::String, gd::InstructionMetadata>&
PlatformExtension::GetAllConditionsForObject(gd::String objectType) {
  if (objectsInfos.find(objectType) != objectsInfos.end())
    return objectsInfos.find(objectType)->second.conditionsInfos;

  return badConditionsMetadata;
}

std::map<gd::String, gd::ExpressionMetadata>&
PlatformExtension::GetAllExpressionsForObject(gd::String objectType) {
  if (objectsInfos.find(objectType) != objectsInfos.end())
    return objectsInfos.find(objectType)->second.expressionsInfos;

  return badExpressionsMetadata;
}

std::map<gd::String, gd::ExpressionMetadata>&
PlatformExtension::GetAllStrExpressionsForObject(gd::String objectType) {
  if (objectsInfos.find(objectType) != objectsInfos.end())
    return objectsInfos.find(objectType)->second.strExpressionsInfos;

  return badStrExpressionsMetadata;
}

std::map<gd::String, gd::InstructionMetadata>&
PlatformExtension::GetAllActionsForBehavior(gd::String autoType) {
  if (behaviorsInfo.find(autoType) != behaviorsInfo.end())
    return behaviorsInfo.find(autoType)->second.actionsInfos;

  return badActionsMetadata;
}

std::map<gd::String, gd::InstructionMetadata>&
PlatformExtension::GetAllConditionsForBehavior(gd::String autoType) {
  if (behaviorsInfo.find(autoType) != behaviorsInfo.end())
    return behaviorsInfo.find(autoType)->second.conditionsInfos;

  return badConditionsMetadata;
}

std::map<gd::String, gd::ExpressionMetadata>&
PlatformExtension::GetAllExpressionsForBehavior(gd::String autoType) {
  if (behaviorsInfo.find(autoType) != behaviorsInfo.end())
    return behaviorsInfo.find(autoType)->second.expressionsInfos;

  return badExpressionsMetadata;
}

std::map<gd::String, gd::ExpressionMetadata>&
PlatformExtension::GetAllStrExpressionsForBehavior(gd::String autoType) {
  if (behaviorsInfo.find(autoType) != behaviorsInfo.end())
    return behaviorsInfo.find(autoType)->second.strExpressionsInfos;

  return badStrExpressionsMetadata;
}

gd::BaseEventSPtr PlatformExtension::CreateEvent(gd::String eventType) const {
  if (eventsInfos.find(eventType) != eventsInfos.end()) {
    if (eventsInfos.find(eventType)->second.instance ==
        std::shared_ptr<BaseEvent>()) {
      std::cout << "ERROR: Extension " << name << " (" << nameSpace << ")"
                << " claims to have event of type " << eventType
                << " but the instance provided is NULL." << std::endl;
      return std::shared_ptr<gd::BaseEvent>();
    }

    return gd::BaseEventSPtr(
        eventsInfos.find(eventType)->second.instance->Clone());
  }

  return std::shared_ptr<gd::BaseEvent>();
}
#endif

CreateFunPtr PlatformExtension::GetObjectCreationFunctionPtr(
    gd::String objectType) const {
  if (objectsInfos.find(objectType) != objectsInfos.end())
    return objectsInfos.find(objectType)->second.createFunPtr;

  return NULL;
}

gd::Behavior* PlatformExtension::GetBehavior(gd::String type) const {
  if (behaviorsInfo.find(type) != behaviorsInfo.end())
    return &behaviorsInfo.find(type)->second.Get();

  return nullptr;
}

gd::BehaviorsSharedData* PlatformExtension::GetBehaviorSharedDatas(
    gd::String type) const {
  if (behaviorsInfo.find(type) != behaviorsInfo.end() &&
      behaviorsInfo.find(type)->second.GetSharedDataInstance())
    return behaviorsInfo.find(type)->second.GetSharedDataInstance();

  return nullptr;
}

void PlatformExtension::SetNameSpace(gd::String nameSpace_) {
  // Most of the builtin extensions do not have namespace
  if (name == "Sprite" || name == "BuiltinObject" || name == "BuiltinAudio" ||
      name == "BuiltinMouse" || name == "BuiltinKeyboard" ||
      name == "BuiltinJoystick" || name == "BuiltinTime" ||
      name == "BuiltinFile" || name == "BuiltinInterface" ||
      name == "BuiltinVariables" || name == "BuiltinCamera" ||
      name == "BuiltinWindow" || name == "BuiltinNetwork" ||
      name == "BuiltinScene" || name == "BuiltinAdvanced" ||
      name == "BuiltinCommonConversions" ||
      name == "BuiltinStringInstructions" ||
      name == "BuiltinMathematicalTools" ||
      name == "Effects" ||      // Well-known effects are not namespaced.
      name == "CommonDialogs")  // New name for BuiltinInterface
  {
    nameSpace = "";
    return;
  }

  nameSpace = nameSpace_ + GetNamespaceSeparator();
}

std::vector<gd::String> PlatformExtension::GetBuiltinExtensionsNames() {
  std::vector<gd::String> builtinExtensions;
  builtinExtensions.push_back("Sprite");
  builtinExtensions.push_back("BuiltinObject");
  builtinExtensions.push_back("BuiltinAudio");
  builtinExtensions.push_back("BuiltinMouse");
  builtinExtensions.push_back("BuiltinKeyboard");
  builtinExtensions.push_back("BuiltinJoystick");
  builtinExtensions.push_back("BuiltinTime");
  builtinExtensions.push_back("BuiltinFile");
  builtinExtensions.push_back("BuiltinVariables");
  builtinExtensions.push_back("BuiltinCamera");
  builtinExtensions.push_back("BuiltinWindow");
  builtinExtensions.push_back("BuiltinNetwork");
  builtinExtensions.push_back("BuiltinScene");
  builtinExtensions.push_back("BuiltinAdvanced");
  builtinExtensions.push_back("BuiltinCommonConversions");
  builtinExtensions.push_back("BuiltinStringInstructions");
  builtinExtensions.push_back("BuiltinMathematicalTools");
  builtinExtensions.push_back("BuiltinExternalLayouts");
  builtinExtensions.push_back("BuiltinCommonInstructions");

  return builtinExtensions;
}

bool PlatformExtension::IsBuiltin() const {
  std::vector<gd::String> builtinExtensions = GetBuiltinExtensionsNames();
  return std::find(builtinExtensions.begin(), builtinExtensions.end(), name) !=
         builtinExtensions.end();
}

#if defined(GD_IDE_ONLY)
void PlatformExtension::StripUnimplementedInstructionsAndExpressions() {
  for (std::map<gd::String, gd::InstructionMetadata>::iterator it =
           GetAllActions().begin();
       it != GetAllActions().end();) {
    if (it->second.codeExtraInformation.functionCallName.empty() &&
        !it->second.codeExtraInformation.HasCustomCodeGenerator()) {
      GetAllActions().erase(it++);
    } else
      ++it;
  }

  for (std::map<gd::String, gd::InstructionMetadata>::iterator it =
           GetAllConditions().begin();
       it != GetAllConditions().end();) {
    if (it->second.codeExtraInformation.functionCallName.empty() &&
        !it->second.codeExtraInformation.HasCustomCodeGenerator()) {
      GetAllConditions().erase(it++);
    } else
      ++it;
  }

  for (std::map<gd::String, gd::ExpressionMetadata>::iterator it =
           GetAllExpressions().begin();
       it != GetAllExpressions().end();) {
    if (it->second.codeExtraInformation.functionCallName.empty() &&
        !it->second.codeExtraInformation.HasCustomCodeGenerator()) {
      GetAllExpressions().erase(it++);
    } else
      ++it;
  }

  for (std::map<gd::String, gd::ExpressionMetadata>::iterator it =
           GetAllStrExpressions().begin();
       it != GetAllStrExpressions().end();) {
    if (it->second.codeExtraInformation.functionCallName.empty() &&
        !it->second.codeExtraInformation.HasCustomCodeGenerator()) {
      GetAllStrExpressions().erase(it++);
    } else
      ++it;
  }

  for (std::map<gd::String, gd::ObjectMetadata>::iterator objIt =
           objectsInfos.begin();
       objIt != objectsInfos.end();
       ++objIt) {
    gd::ObjectMetadata& obj = objIt->second;

    for (std::map<gd::String, gd::InstructionMetadata>::iterator it =
             obj.actionsInfos.begin();
         it != obj.actionsInfos.end();) {
      if (it->second.codeExtraInformation.functionCallName.empty() &&
          !it->second.codeExtraInformation.HasCustomCodeGenerator()) {
        obj.actionsInfos.erase(it++);
      } else
        ++it;
    }

    for (std::map<gd::String, gd::InstructionMetadata>::iterator it =
             obj.conditionsInfos.begin();
         it != obj.conditionsInfos.end();) {
      if (it->second.codeExtraInformation.functionCallName.empty() &&
          !it->second.codeExtraInformation.HasCustomCodeGenerator()) {
        obj.conditionsInfos.erase(it++);
      } else
        ++it;
    }

    for (std::map<gd::String, gd::ExpressionMetadata>::iterator it =
             obj.expressionsInfos.begin();
         it != obj.expressionsInfos.end();) {
      if (it->second.codeExtraInformation.functionCallName.empty() &&
          !it->second.codeExtraInformation.HasCustomCodeGenerator()) {
        obj.expressionsInfos.erase(it++);
      } else
        ++it;
    }

    for (std::map<gd::String, gd::ExpressionMetadata>::iterator it =
             obj.strExpressionsInfos.begin();
         it != obj.strExpressionsInfos.end();) {
      if (it->second.codeExtraInformation.functionCallName.empty() &&
          !it->second.codeExtraInformation.HasCustomCodeGenerator()) {
        obj.strExpressionsInfos.erase(it++);
      } else
        ++it;
    }
  }

  for (std::map<gd::String, gd::BehaviorMetadata>::iterator objIt =
           behaviorsInfo.begin();
       objIt != behaviorsInfo.end();
       ++objIt) {
    gd::BehaviorMetadata& obj = objIt->second;

    for (std::map<gd::String, gd::InstructionMetadata>::iterator it =
             obj.actionsInfos.begin();
         it != obj.actionsInfos.end();) {
      if (it->second.codeExtraInformation.functionCallName.empty() &&
          !it->second.codeExtraInformation.HasCustomCodeGenerator()) {
        obj.actionsInfos.erase(it++);
      } else
        ++it;
    }

    for (std::map<gd::String, gd::InstructionMetadata>::iterator it =
             obj.conditionsInfos.begin();
         it != obj.conditionsInfos.end();) {
      if (it->second.codeExtraInformation.functionCallName.empty() &&
          !it->second.codeExtraInformation.HasCustomCodeGenerator()) {
        obj.conditionsInfos.erase(it++);
      } else
        ++it;
    }

    for (std::map<gd::String, gd::ExpressionMetadata>::iterator it =
             obj.expressionsInfos.begin();
         it != obj.expressionsInfos.end();) {
      if (it->second.codeExtraInformation.functionCallName.empty() &&
          !it->second.codeExtraInformation.HasCustomCodeGenerator()) {
        obj.expressionsInfos.erase(it++);
      } else
        ++it;
    }

    for (std::map<gd::String, gd::ExpressionMetadata>::iterator it =
             obj.strExpressionsInfos.begin();
         it != obj.strExpressionsInfos.end();) {
      if (it->second.codeExtraInformation.functionCallName.empty() &&
          !it->second.codeExtraInformation.HasCustomCodeGenerator()) {
        obj.strExpressionsInfos.erase(it++);
      } else
        ++it;
    }
  }

  for (std::map<gd::String, gd::EventMetadata>::iterator it =
           eventsInfos.begin();
       it != eventsInfos.end();) {
    if (!it->second.HasCustomCodeGenerator())
      eventsInfos.erase(it++);
    else
      ++it;
  }
}
#endif

PlatformExtension::PlatformExtension() : deprecated(false) {}

PlatformExtension::~PlatformExtension() {}

}  // namespace gd
