# Godot Oculus Platform Documentation

## Introduction

This is the documentation site for the Godot Oculus Platform, an implementation of the Oculus Platform SDK for the [Godot Engine](https://godotengine.org).

While you can use this plugin in the editor to get code suggestions, it **only works with the Meta Quest**, not PCVR. If you plan to develop for both the Quest and PCVR, you should add a platform check and only use this plugin when the platform is Android.

Please note that both the documentation and the plugin itself are in development and may be incomplete.

Quick links:

- [Downloads](/godot_oculus_platform/download/)
- [Oculus Platform documentation](https://developer.oculus.com/documentation/native/ps-platform-intro/)

If you find an issue, please report it on the [GitHub issues page](https://github.com/decacis/godot_oculus_platform/issues).

-----

The following table tracks the supported functions from the Oculus Platform SDK:
```
✔️ = Fully implemented
➖ = Partially implemented
❌ = Not implemented yet
```

| Category                                                                    | Status |
|-----------------------------------------------------------------------------|:------:|
| [Platform initialization](/godot_oculus_platform/functions/initialization/) |   ✔️   |
| [Application](/godot_oculus_platform/functions/application/)                |   ✔️   |
| [Abuse Report](/godot_oculus_platform/functions/abuse-report/)              |   ✔️   |
| [User](/godot_oculus_platform/functions/user/)                              |   ✔️   |
| [Achievements](/godot_oculus_platform/functions/achievements/)              |   ✔️   |
| [In-App Purchases](/godot_oculus_platform/functions/in-app-purchases/)      |   ✔️   |
| [Asset Files](/godot_oculus_platform/functions/asset-files/)                |   ✔️   |
| [Leaderboards](/godot_oculus_platform/functions/leaderboards/)              |   ✔️   |
| [Challenges](/godot_oculus_platform/functions/challenges/)                  |   ✔️   |
| Group Presence                                                              |   ❌   |
