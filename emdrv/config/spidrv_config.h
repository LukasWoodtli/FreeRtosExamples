/***************************************************************************//**
 * @file spidrv_config.h
 * @brief SPIDRV configuration file.
 * @version 5.0.0
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/
#ifndef __SILICON_LABS_SPIDRV_CONFIG_H__
#define __SILICON_LABS_SPIDRV_CONFIG_H__

/***************************************************************************//**
 * @addtogroup emdrv
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup SPIDRV
 * @{
 ******************************************************************************/

#warning "This configuration file is deprecated and marked for removal in a later release. Please use the new configuration template file in emdrv\spidrv\config instead."

/// SPIDRV configuration option. Use this define to include the slave part of the SPIDRV API.
#define EMDRV_SPIDRV_INCLUDE_SLAVE

/** @} (end addtogroup SPIDRV) */
/** @} (end addtogroup emdrv) */

#endif /* __SILICON_LABS_SPIDRV_CONFIG_H__ */
