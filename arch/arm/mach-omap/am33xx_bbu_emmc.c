/*
 * Copyright (c) 2015 Phytec Messtechnik GmbH
 * Author: Daniel Schultz <d.schultz@phytec.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <common.h>
#include <malloc.h>
#include <bbu.h>
#include <fs.h>
#include <fcntl.h>
#include <filetype.h>

static int emmc_mlo_handler(struct bbu_handler *handler, struct bbu_data *data)
{
	int ret = 0;
	int i = 0;
	int fd;
	const void *image = data->image;
	size_t size = data->len;

	if (file_detect_type(image, size) != filetype_ch_image) {
		pr_err("%s is not a valid ch-image\n", data->imagefile);
		return -EINVAL;
	}
	ret = bbu_confirm(data);
	if (ret != 0)
		return ret;

	fd = open(handler->devicefile, O_WRONLY);
	if (fd < 0) {
		pr_err("could not open %s: %s\n", handler->devicefile,
			errno_str());
		return fd;
	}

	for (i = 1; i < 4; i++) {
		ret = pwrite(fd, image, size, i * 0x20000);
		if (ret < 0) {
			pr_err("could not write to fd %s: %s\n",
				handler->devicefile, errno_str());
			close(fd);
			return ret;
		}
	}
	close(fd);

	printf("Remove the MLO from the %s boot partition.\nOtherwise the wrong MLO may be loaded!\n",
		handler->devicefile);

	return 0;
}

int am33xx_bbu_emmc_mlo_register_handler(const char *name, char *devicefile)
{
	struct bbu_handler *handler;
	int ret;

	handler = xzalloc(sizeof(*handler));
	handler->devicefile = devicefile;
	handler->name = name;
	handler->handler = emmc_mlo_handler;

	ret = bbu_register_handler(handler);

	if (ret)
		free(handler);

	return ret;
}
