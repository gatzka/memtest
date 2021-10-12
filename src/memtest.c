/*
 * SPDX-License-Identifier: MIT
 *
 * The MIT License (MIT)
 *
 * Copyright (c) <2020> <Stephan Gatzka>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * The credits for this source code mostly go to Michael Barr. This
 * source code is heavily based on:
 * https://barrgroup.com/embedded-systems/how-to/memory-test-suite-c
 */

#include <limits.h>
#include <stddef.h>

#include "memtest.h"

datum_t memtest_databus(datum_t *address)
{
	volatile datum_t *addr = address;

	for (datum_t pattern = 1; pattern != 0; pattern <<= 1U) {
		*addr = pattern;

		if (*addr != pattern) {
			return pattern;
		}
	}

	return 0;
}

datum_t *memtest_addressbus(datum_t *base_address, size_t nbytes)
{
	static const uint8_t PATTERN_BYTE = UINT8_C(0xAA);
	static const uint8_t ANTI_PATTERN_BYTE = UINT8_C(0x55);

	datum_t mem_pattern = 0;
	datum_t mem_anti_pattern = 0;

	for (unsigned int i = 0; i < sizeof(mem_pattern); i++) {
		mem_pattern = (mem_pattern << (unsigned int)CHAR_BIT) | PATTERN_BYTE;
	}

	for (unsigned int i = 0; i < sizeof(mem_anti_pattern); i++) {
		mem_anti_pattern = (mem_anti_pattern << (unsigned int)CHAR_BIT) | ANTI_PATTERN_BYTE;
	}

	size_t address_mask = (nbytes / sizeof(datum_t) - 1);
	size_t offset = 0;
	size_t test_offset = 0;

	volatile datum_t *base_addr = base_address;

	datum_t pattern = mem_pattern;
	datum_t antipattern = mem_anti_pattern;

	for (offset = 1; (offset & address_mask) != 0; offset <<= 1U) {
		base_addr[offset] = pattern;
	}

	/*
	 * Check for address bits stuck high.
	 */
	test_offset = 0;
	base_addr[test_offset] = antipattern;

	for (offset = 1; (offset & address_mask) != 0; offset <<= 1U) {
		if (base_addr[offset] != pattern) {
			return &base_address[offset];
		}
	}

	base_addr[test_offset] = pattern;

	/*
	 * Check for address bits stuck low or shorted.
	 */
	for (test_offset = 1; (test_offset & address_mask) != 0; test_offset <<= 1U) {
		base_addr[test_offset] = antipattern;

		if (base_addr[0] != pattern) {
			return &base_address[test_offset];
		}

		for (offset = 1; (offset & address_mask) != 0; offset <<= 1U) {
			if ((base_addr[offset] != pattern) && (offset != test_offset)) {
				return &base_address[test_offset];
			}
		}

		base_addr[test_offset] = pattern;
	}

	return NULL;
}

datum_t *memtest_device(datum_t *base_address, size_t nbytes)
{
	volatile size_t offset = 0;
	volatile size_t nwords = nbytes / sizeof(datum_t);
	volatile datum_t *base_addr = base_address;

	volatile datum_t pattern = 0;
	volatile datum_t antipattern = 0;

	/*
	 * Fill memory with a known pattern.
	 */
	for (pattern = 1, offset = 0; offset < nwords; pattern++, offset++) {
		base_addr[offset] = pattern;
	}

	/*
	 * Check each location and invert it for the second pass.
	 */
	for (pattern = 1, offset = 0; offset < nwords; pattern++, offset++) {
		if (base_addr[offset] != pattern) {
			return &base_address[offset];
		}

		antipattern = ~pattern;
		base_addr[offset] = antipattern;
	}

	/*
	 * Check each location for the inverted pattern.
	 */
	for (pattern = 1, offset = 0; offset < nwords; pattern++, offset++) {
		antipattern = ~pattern;
		if (base_addr[offset] != antipattern) {
			return &base_address[offset];
		}
	}

	return (datum_t *)NULL;
}
