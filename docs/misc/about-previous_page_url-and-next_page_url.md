# About previous_page_url and next_page_url

Certain methods return a `Dictionary` with: `previous_page_url` and/or `next_page_url`. Both of these keys can theoretically contain a URL where you could extract the previous (or next) set of records. However, I tested a few methods with up to 1000 records and didn't manage to get a `previous_page_url` or `next_page_url`, so I imagine this pagination concept was deprecated at some point, but there is no documentation about it, so I decided to include it in the response just in case.

If you happen to get this URL, please report it on the [issues page](https://github.com/decacis/godot_oculus_platform/issues) in GitHub, so we are aware that it can happen and update the docs.