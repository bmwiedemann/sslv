/*
 * OpenSSL / BoringSSL
 */
int
X509_verify_cert(void)
{
	return (1);
}

/* LibreSSL */
int
_libre_X509_verify_cert(void)
{
	return (1);
}

long
SSL_get_verify_result(void)
{
	return (0);
}

/*
 * GnuTLS
 */
int
gnutls_certificate_verify_peers(void)
{
	return (0);
}

int
gnutls_session_get_verify_cert_status(void)
{
	return (0);
}

/*
 * NSS
 */
int
CERT_VerifyCert(void)
{
	return (0);
}
int CERT_VerifySignedData(void) { return (0); }
int PK11_Verify(void) { return (0); }
int PK11_VerifyKeyOK(void) { return (0); }
int CERT_VerifyCertNow(void) { return (0); }
int CERT_PKIXVerifyCert(void) { return (0); }
int CERT_CertTimesValid(void) { return (0); }
int CERT_VerifyCertificateNow(void) { return (0); }
int CERT_VerifyCACertForUsage(void) { return (0); }
int CERT_CheckCertUsage(void) { return (0); }

int
CERT_VerifyCertificate(void)
{
	return (0);
}

/* Gnupg key expiry */
#define _GNU_SOURCE
#include <dlfcn.h>
#include <gpgme.h>
#include <stdlib.h>
#include <string.h>

static gpgme_verify_result_t fake_result;

gpgme_verify_result_t
gpgme_op_verify_result(gpgme_ctx_t ctx)
{
    (void)ctx;

    if (fake_result)
        return fake_result;

    fake_result = calloc(1, sizeof(*fake_result));
    fake_result->signatures = calloc(1, sizeof(*fake_result->signatures));

    gpgme_signature_t sig = fake_result->signatures;

    sig->status   = GPG_ERR_NO_ERROR;
    sig->validity = GPGME_VALIDITY_FULL;
    sig->summary  = 0;

    sig->fpr = strdup("AD485664E901B867051AB15F35A2F86E29B700A4");

    return fake_result;
}
