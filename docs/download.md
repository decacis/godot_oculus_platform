# Download
------

The interactive list bellow will help you find all of the precompiled releases from a combination of Godot and Oculus Platform SDK versions:

<div>
    Godot version <select name="gd-versions" id="gd-versions"></select> with Oculus Platform SDK version <select name="sdk-versions" id="sdk-versions"></select>
    <ul id="gdop-dl-links">
    </ul>
</div>
<script>
    const gdop_versions = {
        "4.0.x": {
            "51": [
                {
                    "name": "v0.0.1-alpha",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v0.0.1-alpha"
                },
            ],
            "53": [
                {
                    "name": "v1.0.0-beta",
                    "url": "https://github.com/decacis/godot_oculus_platform/releases/tag/v1.0.0-beta"
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
        sdk_versions.sort((a, b) => b - a);

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

        dl_links.forEach(link => {
            let temp_li = document.createElement('li');
            let temp_a = document.createElement('a');

            temp_a.href = link.url;
            temp_a.innerText = link.name;

            temp_li.appendChild(temp_a);
            dl_links_el.appendChild(temp_li);
        });
    }
</script>

------

You can find all the releases in the [GitHub releases page](https://github.com/decacis/godot_oculus_platform/releases).

In-development precompiled versions can be found in the [GitHub actions page](https://github.com/decacis/godot_oculus_platform/actions?query=branch%3Amain).