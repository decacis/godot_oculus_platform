# Download
------

The interactive list bellow will help you find all of the precompiled releases from a combination of Godot and Oculus Platform SDK versions:

<div>
    Godot version <select name="gd-versions" id="gd-versions"></select> with Oculus Platform SDK version <select name="sdk-versions" id="sdk-versions"></select>
    <ul id="gdop-dl-links">
    </ul>
</div>
<style>
    .version-link {
        transition: 0.15s;
    }
    .version-link:hover {
        opacity: 1.0 !important;
    }
</style>
<script>
    const gdop_versions = {
        "4.0.2-stable": {
            "51.0": [
                {
                    "name": "v0.0.1-alpha",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v0.0.1-alpha"
                },
            ],
            "53.0": [
                {
                    "name": "v1.0.0-beta",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v1.0.0-beta_godot-4.0.2-stable_sdk-53.0"
                },
                {
                    "name": "v0.2.5-alpha",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v0.2.5-alpha"
                },
                {
                    "name": "v0.2.0-alpha",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v0.2.0-alpha"
                },
                {
                    "name": "v0.1.5-alpha",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v0.1.5-alpha"
                },
                {
                    "name": "v0.1.0-alpha",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v0.1.0-alpha"
                },
            ]
        },
        "4.0.3-stable": {
            "53.0": [
                {
                    "name": "v1.2.1-beta",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v1.2.1-beta_godot-4.0.3-stable_sdk-53.0"
                },
                {
                    "name": "v1.2.0-beta",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v1.2.0-beta_godot-4.0.3-stable_sdk-53.0"
                },
                {
                    "name": "v1.1.0-beta",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v1.1.0-beta_godot-4.0.3-stable_sdk-53.0"
                },
                {
                    "name": "v1.0.0-beta",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v1.0.0-beta_godot-4.0.3-stable_sdk-53.0"
                },
            ]
        },
        "4.1.0-stable": {
            "53.0": [
                {
                    "name": "v1.2.2-beta",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v1.2.2-beta_godot-4.1.0-stable_sdk-53.0"
                },
                {
                    "name": "v1.2.1-beta",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v1.2.1-beta_godot-4.1.0-stable_sdk-53.0"
                }
            ]
        },
        "4.1.2-stable": {
            "56.0": [
                {
                    "name": "v1.3.0-beta",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v1.3.0-beta_godot-4.1.2-stable_sdk-56.0"
                }
            ],
            "57.0": [
                {
                    "name": "v1.3.1-beta",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v1.3.1-beta_godot-4.1.2-stable_sdk-57.0"
                }
            ]
        },
        "4.1.3-stable": {
            "57.0": [
                {
                    "name": "v1.3.2-beta",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v1.3.2-beta_godot-4.1.3-stable_sdk-57.0"
                }
            ],
            "59.0": [
                {
                    "name": "v1.3.3-beta",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v1.3.3-beta_godot-4.1.3-stable_sdk-59.0"
                }
            ]
        },
        "4.2.0-stable": {
            "59.0": [
                {
                    "name": "v1.4.0-beta",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v1.4.0-beta_godot-4.2.0-stable_sdk-59.0"
                }
            ]
        },
        "4.2.0+": {
            "66.0": [
                {
                    "name": "v1.5.0",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v1.5.0_godot-4.2.0-stable_sdk-66.0"
                }
            ],
            "67.0": [
                {
                    "name": "v1.5.1",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v1.5.1_godot-4.2.0-stable_sdk-67.0"
                }
            ]
        }
    }

    const gd_versions_el = document.getElementById('gd-versions');
    const sdk_versions_el = document.getElementById('sdk-versions');
    const dl_links_el = document.getElementById('gdop-dl-links');

    let selected_gd_version = '';
    let selected_sdk_version = '';

    gd_versions_el.addEventListener('change', ev => {
        selected_gd_version = ev.target.value;
        renderOculusVersions();
    })

    sdk_versions_el.addEventListener('change', ev => {
        selected_sdk_version = ev.target.value;
        sdkVersionChanged();
    })

    window.addEventListener('DOMContentLoaded', ev => {
        renderGDVersions();
    })

    function renderGDVersions() {
        let gd_versions = Object.keys(gdop_versions);
        gd_versions.sort((a, b) => {
            let a_plus = a.replace(/[^0-9+]+/g, '');
            let b_plus = b.replace(/[^0-9+]+/g, '');

            let temp_a = Number(a_plus.replace(/\+/g, '.1'));
            let temp_b = Number(b_plus.replace(/\+/g, '.1'));

            return temp_b - temp_a;
        });

        for (let i = 0; i < gd_versions.length; i++) {
            if(i == 0) selected_gd_version = gd_versions[i];

            let temp_val = document.createElement('option');
            temp_val.value = gd_versions[i];
            temp_val.innerText = gd_versions[i];

            gd_versions_el.appendChild(temp_val);
        }

        renderOculusVersions();
    }

    function renderOculusVersions() {
        let sdk_versions = Object.keys(gdop_versions[selected_gd_version]);
        sdk_versions.sort((a, b) => Number(b) - Number(a));

        while (sdk_versions_el.hasChildNodes()) {
            sdk_versions_el.removeChild(sdk_versions_el.lastChild);
        }

        for (let i = 0; i < sdk_versions.length; i++) {
            if(i == 0) selected_sdk_version = sdk_versions[i];

            let temp_val = document.createElement('option');
            temp_val.value = sdk_versions[i];
            temp_val.innerText = sdk_versions[i];

            sdk_versions_el.appendChild(temp_val);
        }

        updateLink()
    }

    function sdkVersionChanged() {
        updateLink();
    }

    function updateLink() {
        let dl_links = gdop_versions[selected_gd_version][selected_sdk_version];

        while (dl_links_el.hasChildNodes()) {
            dl_links_el.removeChild(dl_links_el.lastChild);
        }

        const gradient_step = 0.7 / dl_links.length;

        for (let i = 0; i < dl_links.length; i++) {
            let temp_gradient_step = gradient_step * i;
            
            let temp_li = document.createElement('li');
            let temp_a = document.createElement('a');

            temp_a.href = dl_links[i].url;
            temp_a.innerText = dl_links[i].name;
            temp_a.target = "_blank";

            temp_li.classList.add('version-link');
            temp_li.appendChild(temp_a);
            dl_links_el.appendChild(temp_li);

            temp_li.style.opacity = 1.0 - temp_gradient_step;
        }
    }
</script>

------

/// admonition | Note
    type: warning
Make sure to enable the `Godot Oculus Platform` plugin in your Project Settings.

Also, most of the methods will require you to enable the `INTERNET` permission in your export settings/add it to your AndroidManifest.xml
///

You can find all the releases in the [GitHub releases page](https://github.com/decacis/godot_oculus_platform/releases).

In-development precompiled versions can be found in the [GitHub actions page](https://github.com/decacis/godot_oculus_platform/actions?query=branch%3Amain).