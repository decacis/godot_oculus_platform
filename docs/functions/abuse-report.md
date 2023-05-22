# Functions - Abuse Report
Related Oculus Platform documentation:

- [User Reporting FAQs](https://developer.oculus.com/faqs#faq_856753478660534)
- [https://developer.oculus.com/resources/reporting-service/](https://developer.oculus.com/resources/reporting-service/)
- [https://developer.oculus.com/resources/reporting-plugin](https://developer.oculus.com/resources/reporting-plugin)

------
## Signals

### abouse_report_form_requested
//// admonition | About
    type: abstract
This signal will be emitted when the user presses the abuse report button. You have to then let the Oculus Platform if you handled the notification or not. See 
////

------
## abuse_report_request_handled
//// admonition | abuse_report_request_handled(report_request_response : `ReportRequestResponse`)
    type: abstract

Informs the Oculus Platform about whether we handled the notification or not. You want to respond with `handled` if you showed an in-game form or UI to handle the user report request.

On the other hand, if the player is in the tutorial for example, and they are not interacting with other users, you can respond with `unhandled` and ideally let the user know that they can't create an abuse report in that part of your app.

**NOTE:** if you use the Reporting Service provided by Meta, a UI will be shown automatically. I don't really know if you *have* to set the request as handled in that case, but it doesn't hurt informing that you handled the request anyway.

**Returns:** A `GDOculusPlatformPromise` that will contain a `true` `bool` if the request was fulfilled. The promise will error if the request couldn't be completed.

Enums:

**ReportRequestResponse**

| Name                       |  Value  | Description                                                      |
|----------------------------|:-------:|------------------------------------------------------------------|
| REPORT_REQUEST_HANDLED     |    1    | The app showed a form/UI to handle the abuse report.             |
| REPORT_REQUEST_UNHANDLED   |    2    | The app decided not to show a form/UI and informed the user why. |

/// details | Example
    type: example
``` gdscript linenums="1"
GDOculusPlatform.abouse_report_form_requested.connect(_handle_abuse_report_req)

func _handle_abuse_report_req():

    # SHOW ABUSE REPORT UI

    # Let platform know that we handled the request
    GDOculusPlatform.abuse_report_request_handled(GDOculusPlatform.REPORT_REQUEST_HANDLED)\
    .error(func(request_error):
        print("Unable to send handled response: ", request_error)
    )
```
///
////
