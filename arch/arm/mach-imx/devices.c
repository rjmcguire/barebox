#include <common.h>
#include <driver.h>
#include <mach/devices.h>

static inline struct device_d *imx_add_device(char *name, int id, void *base, int size, void *pdata)
{
	return add_generic_device(name, id, NULL, (resource_size_t)base, size,
				  IORESOURCE_MEM, pdata);
}

struct device_d *imx_add_fec(void *base, struct fec_platform_data *pdata)
{
	return imx_add_device("fec_imx", -1, base, 0x1000, pdata);
}

struct device_d *imx_add_spi(void *base, int id, struct spi_imx_master *pdata)
{
	return imx_add_device("imx_spi", id, base, 0x1000, pdata);
}

struct device_d *imx_add_i2c(void *base, int id, struct i2c_platform_data *pdata)
{
	return imx_add_device("i2c-imx", id, base, 0x1000, pdata);
}

struct device_d *imx_add_uart(void *base, int id)
{
	return imx_add_device("imx_serial", id, base, 0x1000, NULL);
}

struct device_d *imx_add_nand(void *base, struct imx_nand_platform_data *pdata)
{
	return imx_add_device("imx_nand", -1, base, 0x1000, pdata);
}

struct device_d *imx_add_fb(void *base, struct imx_fb_platform_data *pdata)
{
	return imx_add_device("imxfb", -1, base, 0x1000, pdata);
}

struct device_d *imx_add_ipufb(void *base, struct imx_ipu_fb_platform_data *pdata)
{
	return imx_add_device("imx-ipu-fb", -1, base, 0x1000, pdata);
}

struct device_d *imx_add_mmc(void *base, int id, void *pdata)
{
	return imx_add_device("imx-mmc", id, base, 0x1000, pdata);
}

struct device_d *imx_add_esdhc(void *base, int id, struct esdhc_platform_data *pdata)
{
	return imx_add_device("imx-esdhc", id, base, 0x1000, pdata);
}

struct device_d *imx_add_kpp(void *base, struct matrix_keymap_data *pdata)
{
       return imx_add_device("imx-kpp", -1, base, 0x1000, pdata);
}