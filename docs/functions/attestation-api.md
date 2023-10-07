# Functions - Attestation API
Related Oculus Platform documentation:

- [https://developer.oculus.com/documentation/native/ps-attestation-api/](https://developer.oculus.com/documentation/native/ps-attestation-api/)

------

## deviceappintegrity_get_integrity_token
//// admonition | deviceappintegrity_get_integrity_token(challenge_nonce : `String`)
    type: abstract

Requests the integrity (attestation) token to be used to verify the app integrity.

**Returns:** A `GDOculusPlatformPromise` that will contain a `String` with the attestation token. The promise will error if the request couldn't be completed.

/// details | Example
    type: example
``` gdscript linenums="1"
# We have a nonce from the Application Server
var nonce : String = "R29kb3QgT2N1bHVzIFBsYXRmb3Jt"

GDOculusPlatform.deviceappintegrity_get_integrity_token(nonce)\
.then(func(attestation_token : String):
    # Now we use this token to verify the app integrity
    # You could use an HTTPRequest for example
    print("Attestation token: ", attestation_token)
)\
.error(func(attestation_token_err):
    print("Unable to retrieve the attestation token: ", attestation_token_err)
)
```
///
////
