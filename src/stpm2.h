#ifndef __STPM2_H__
#define __STPM2_H__

#include <stdint.h>

#include <tss2/tss2_sys.h>

#define STPM2_RSA_ENC_MESSAGE_SIZE (2048 / 8)

typedef struct {
	TSS2_SYS_CONTEXT	*sys_ctx;
	TSS2_TCTI_CONTEXT	*tcti_ctx;

	void 	*tcti_so_handle;

	TPM2_HANDLE		primary_handle;

	struct {
		TPM2_HANDLE	handle;
		TPM2B_PUBLIC	pub;
		TPM2B_PRIVATE	priv;
	} current_rsa_key;
} stpm2_context;

typedef enum {
	STPM2_HASH_ALG_SHA1,
	STPM2_HASH_ALG_SHA256,
	STPM2_HASH_ALG_SHA384,
	STPM2_HASH_ALG_SHA512,
} stpm2_hash_alg;

int stpm2_init(stpm2_context *ctx);
int stpm2_free(stpm2_context *ctx);

int stpm2_get_random(stpm2_context *ctx, uint8_t *buf, size_t size);
int stpm2_hash(stpm2_context *ctx, stpm2_hash_alg alg, const uint8_t *buf, size_t size, uint8_t *outbuf, size_t outsize);

int stpm2_unload_key(stpm2_context *ctx);
int stpm2_create_rsa_2048(stpm2_context *ctx);

int stpm2_export_pubkey_pem(stpm2_context *ctx, const char *path);
int stpm2_export_key(stpm2_context *ctx, const char *path);
int stpm2_load_key(stpm2_context *ctx, const char *path);

int stpm2_rsa_encrypt(stpm2_context *ctx, uint8_t *in, size_t insize, uint8_t *out, size_t outsize);
int stpm2_rsa_decrypt(stpm2_context *ctx, uint8_t *in, size_t insize, uint8_t *out, size_t outsize, size_t *actual_size);

#endif /* __STPM2_H__ */
