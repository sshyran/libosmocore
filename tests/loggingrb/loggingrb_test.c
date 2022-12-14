/* simple test for the debug interface */
/*
 * (C) 2008, 2009 by Holger Hans Peter Freyther <zecke@selfish.org>
 * (C) 2012-2013 by Katerina Barone-Adesi <kat.obsc@gmail.com>
 * All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <osmocom/core/logging.h>
#include <osmocom/core/utils.h>
#include <osmocom/core/loggingrb.h>

enum {
	DRLL,
	DCC,
	DMM,
};

static const struct log_info_cat default_categories[] = {
	[DRLL] = {
		  .name = "DRLL",
		  .description = "A-bis Radio Link Layer (RLL)",
		  .color = OSMO_LOGCOLOR_RED,
		  .enabled = 1, .loglevel = LOGL_NOTICE,
		  },
	[DCC] = {
		 .name = "DCC",
		 .description = "Layer3 Call Control (CC)",
		 .color = OSMO_LOGCOLOR_GREEN,
		 .enabled = 1, .loglevel = LOGL_NOTICE,
		 },
	[DMM] = {
		 .name = NULL,
		 .description = "Layer3 Mobility Management (MM)",
		 .color = OSMO_LOGCOLOR_BLUE,
		 .enabled = 1, .loglevel = LOGL_NOTICE,
		 },
};

const struct log_info log_info = {
	.cat = default_categories,
	.num_cat = ARRAY_SIZE(default_categories),
};

int main(int argc, char **argv)
{
	struct log_target *ringbuf_target;

	log_init(&log_info, NULL);
	ringbuf_target = log_target_create_rb(0x1000);
	log_add_target(ringbuf_target);
	log_set_all_filter(ringbuf_target, 1);
	log_set_print_filename2(ringbuf_target, LOG_FILENAME_NONE);
	log_set_print_category(ringbuf_target, 0);
	log_set_print_category_hex(ringbuf_target, 0);

	log_parse_category_mask(ringbuf_target, "DRLL:DCC");
	log_parse_category_mask(ringbuf_target, "DRLL");
	DEBUGP(DCC, "You should not see this\n");

	log_parse_category_mask(ringbuf_target, "DRLL:DCC");
	DEBUGP(DRLL, "You should see this\n");
	DEBUGP(DCC, "You should see this\n");
	DEBUGP(DMM, "You should not see this\n");
	fprintf(stderr, "%s", log_target_rb_get(ringbuf_target, 0));
	fprintf(stderr, "%s", log_target_rb_get(ringbuf_target, 1));
	OSMO_ASSERT(!log_target_rb_get(ringbuf_target, 2));

	return 0;
}
