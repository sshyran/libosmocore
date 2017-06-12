/* (C) 2012 by Harald Welte <laforge@gnumonks.org>
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
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <unistd.h>
#include <osmocom/core/utils.h>

#include <osmocom/gsm/protocol/gsm_44_318.h>

/*! \file gan.c
 *  \brief Generic Access Network (GAN) / UMA according to TS 44.318
 */


const struct value_string gan_msgt_vals[] = {
	{ GA_MT_RC_DISCOVERY_REQUEST,	"GA-RC DISCOVERY REQUEST" },
	{ GA_MT_RC_DISCOVERY_ACCEPT,	"GA-RC DISCOVERY ACCEPT" },
	{ GA_MT_RC_DISCOVERY_REJECT,	"GA-RC DISCOVERY REJECT" },
	{ GA_MT_RC_REGISTER_REQUEST,	"GA-RC REGISTER REQUEST" },
	{ GA_MT_RC_REGISTER_ACCEPT,	"GA-RC REGISTER ACCEPT" },
	{ GA_MT_RC_REGISTER_REDIRECT,	"GA-RC REGISTER REDIRECT" },
	{ GA_MT_RC_REGISTER_REJECT,	"GA-RC REGISTER REJECT" },
	{ GA_MT_RC_DEREGISTER,		"GA-RC DEREGISTER" },
	{ GA_MT_RC_REGISTER_UPDATE_UL,	"GA-RC REGISTER UPDATE UL" },
	{ GA_MT_RC_REGISTER_UPDATE_DL,	"GA-RC REGISTER UPDATE DL" },
	{ GA_MT_RC_CELL_BCAST_INFO,	"GA-RC CELL BROADCAST INFO" },
	{ GA_MT_CSR_CIPH_MODE_CMD,	"GA-CSR CIPHER MDOE COMMAND" },
	{ GA_MT_CSR_CIPH_MODE_COMPL,	"GA-CSR CIPHER MODE COMPLETE" },
	{ GA_MT_CSR_ACT_CHAN,		"GA-CSR ACTIVATE CHANNEL" },
	{ GA_MT_CSR_ACT_CHAN_ACK,	"GA-CSR ACTIVATE CHANNEL ACK" },
	{ GA_MT_CSR_ACT_CHAN_COMPL,	"GA-CSR ACTIVATE CHANNEL COMPLETE" },
	{ GA_MT_CSR_ACT_CHAN_FAIL,	"GA-CSR ACTIVATE CHANNEL FAIL" },
	{ GA_MT_CSR_CHAN_MODE_MOD,	"GA-CSR CHANNEL MODE MODIFY" },
	{ GA_MT_CSR_CHAN_MODE_MOD_ACK,	"GA-CSR CHANNEL MODE MODIFY ACK" },
	{ GA_MT_CSR_RELEASE,		"GA-CSR RELEASE" },
	{ GA_MT_CSR_RELEASE_COMPL,	"GA-CSR RELEASE COMPLETE" },
	{ GA_MT_CSR_CLEAR_REQ,		"GA-CSR CLEAR REQUEST" },
	{ GA_MT_CSR_HO_ACCESS,		"GA-CSR HANDOVER ACCESS" },
	{ GA_MT_CSR_HO_COMPL,		"GA-CSR HANDOVER COMPLETE" },
	{ GA_MT_CSR_UL_QUAL_IND,	"GA-CSR UL QUALITY INDICATION" },
	{ GA_MT_CSR_HO_INFO,		"GA-CSR HANDOVER INFO" },
	{ GA_MT_CSR_HO_CMD,		"GA-CSR HANDOVER COMMAND" },
	{ GA_MT_CSR_HO_FAIL,		"GA-CSR HANDOVER FAILURE" },
	{ GA_MT_CSR_PAGING_REQ,		"GA-CSR PAGING REQUEST" },
	{ GA_MT_CSR_PAGING_RESP,	"GA-CSR PAGING RESPONSE" },
	{ GA_MT_CSR_UL_DIRECT_XFER,	"GA-CSR UL DIRECT TRANSFER" },
	{ GA_MT_CSR_DL_DIRECT_XFER,	"GA-CSR DL DIRECT TRANSFER" },
	{ GA_MT_CSR_STATUS,		"GA-CSR STATUS" },
	{ GA_MT_RC_KEEPALIVE,		"GA-CSR KEEPALIVE" },
	{ GA_MT_CSR_CM_ENQ,		"GA-CSR CLASSMARK ENQUIRY" },
	{ GA_MT_CSR_CM_CHANGE,		"GA-CSR CLASSMARK CHANGE" },
	{ GA_MT_PSR_GPRS_SUSPEND_REQ,	"GA-PSR GPRS SUSPEND REQUEST" },
	{ GA_RC_SYNC_INFO,		"GA-RC SYNCH INFORMATION" },
	{ GA_CSR_UTRAN_CM_CHG,		"GA-CSR UTRAN CLASSMARK CHANGE" },
	{ GA_MT_CSR_REQUEST,		"GA-CSR REQUEST" },
	{ GA_MT_CSR_REQUEST_ACCEPT,	"GA-CSR REQUEST ACCEPT" },
	{ GA_MT_CSR_REQUEST_REJECT,	"GA-CSR REQUEST REJECT" },
	{ 0, NULL }
};

const struct value_string gan_pdisc_vals[] = {
	{ GA_PDISC_RC,			"RC" },
	{ GA_PDISC_CSR,			"CSR" },
	{ GA_PDISC_PSR,			"PSR" },
	{ 0, NULL }
};

