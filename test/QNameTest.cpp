/*
* Copyright (c) 2018, Private Octopus, Inc.
* All rights reserved.
*
* Permission to use, copy, modify, and distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL Private Octopus, Inc. BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "DnsStats.h"
#include "QNameTest.h"

static uint8_t p1[] = {
    0x12, 0x23, 0x80, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01,
    0x03, 'w', 'w', 'w', 0x07, 'e', 'x', 'a', 'm', 'p', 'l', 'e', 0x03, 'c', 'o', 'm', 0x00, 0x00, 0x01, 0x00, 0x01,
    0xC0, 0x18, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x04, 'r', 'o', 'o', 't', 0x04, 'a', 'r', 'p', 'a', 0x00,
    0xC0, 0x18, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x04, 0x0A, 0x00, 0x00, 0x01
};

static uint8_t p2[] = {
    0x12, 0x23, 0x80, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01,
    0x03, 'w', 'w', 'w', 0x07, 'e', 'x', 'a', 'm', 'p', 'l', 'e', 0x03, 'c', 'o', 'm', 0x00, 0x00, 0x01, 0x00, 0x01,
    0x07, 'e', 'x', 'a', 'm', 'p', 'l', 'e', 0x03, 'c', 'o', 'm', 0x00, 0x00, 0x01, 0x00, 0x02,  0x00, 0x08, 0x02, 'n', 's', 0xC0, 0x21,
    0xC0, 0x34, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x04, 0x0A, 0x00, 0x00, 0x01
};

static uint8_t p3[] = {
    0x12, 0x23, 0x80, 0x00,
    0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x03, 'w', 'w', 'w', 0x07, 'e', 'x', 'a', 'm', 'p', 'l', 'e', 0x03, 'c', 'o', 'm', 0x00, 0x00, 0x01, 0x00, 0x01,
    0xC0, 0x0C, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x04, 0x0A, 0x00, 0x00, 0x01
};

static uint8_t p4[] = {
    0x12, 0x23, 0x80, 0x00,
    0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x07, 'e', 'x', 'a', 'm', 'p', 'l', 'e', 0x03, 'c', 'o', 'm', 0x00, 0x00, 0x01, 0x00, 0x01,
    0xC0, 0x0C, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x04, 0x0A, 0x00, 0x00, 0x01
};

static uint8_t p5[] = {
    0x12, 0x23, 0x80, 0x00,
    0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x07, 'e', 'x', 'a', 'm', 'p', 'l', 'e', 0x03, 'c', 'o', 'm', 0x00, 0x00, 0x01, 0x00, 0x01,
    0x07, 'E', 'x', 'A', 'm', 'P', 'l', 'E', 0x03, 'c', 'o', 'm', 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x04, 0x0A, 0x00, 0x00, 0x01
};

static uint8_t p6[] = {
    0x12, 0x23, 0x80, 0x00,
    0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x07, 'e', 'X', 'a', 'M', 'p', 'L', 'e', 0x03, 'c', 'o', 'm', 0x00, 0x00, 0x01, 0x00, 0x01,
    0x07, 'E', 'x', 'A', 'm', 'P', 'l', 'E', 0x03, 'c', 'o', 'm', 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x04, 0x0A, 0x00, 0x00, 0x01
};

static uint8_t p7[] = {
    0x12, 0x23, 0x80, 0x00,
    0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x07, 'e', 'x', 'a', 'm', 'p', 'l', 'e', 0x03, 'c', 'o', 'm', 0x00, 0x00, 0x01, 0x00, 0x01,
    0xC0, 0x0C, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x04, 0x0A, 0x00, 0x00, 0x01
};

static uint8_t p8[] = {
    0x12, 0x23, 0x80, 0x00,
    0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
    0x07, 'e', 'x', 'a', 'm', 'p', 'l', 'e', 0x03, 'c', 'o', 'm', 0x00, 0x00, 0x01, 0x00, 0x02,
    0x07, 'e', 'x', 'a', 'm', 'p', 'l', 'e', 0x03, 'c', 'o', 'm', 0x00, 0x00, 0x01, 0x00, 0x02,  0x00, 0x08, 0x02, 'n', 's', 0xC0, 0x21,
    0xC0, 0x34, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x04, 0x0A, 0x00, 0x00, 0x01
};

static uint8_t p9[] = {
    0x12, 0x23, 0x80, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01,
    0x07, 'e', 'x', 'a', 'm', 'p', 'l', 'e', 0x03, 'c', 'o', 'm', 0x00, 0x00, 0x01, 0x00, 0x01,
    0x07, 'e', 'x', 'a', 'm', 'p', 'l', 'e', 0x03, 'c', 'o', 'm', 0x00, 0x00, 0x01, 0x00, 0x02,  0x00, 0x08, 0x02, 'n', 's', 0xC0, 0x21,
    0xC0, 0x34, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x04, 0x0A, 0x00, 0x00, 0x01
};

static uint8_t p10[] = {
    0x12, 0x23, 0x80, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01,
    0x03, 'c', 'o', 'm', 0x00, 0x00, 0x01, 0x00, 0x01,
    0xC0, 0x0C, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x04, 'r', 'o', 'o', 't', 0x04, 'a', 'r', 'p', 'a', 0x00,
    0xC0, 0x0C, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x04, 0x0A, 0x00, 0x00, 0x01
};

static uint8_t p11[] = {
    0x12, 0x23, 0x80, 0x00,
    0x00, 0x02, 0x00,0x00, 0x00, 0x01, 0x00, 0x01,
    0x03, 'c', 'o', 'm', 0x00, 0x00, 0x01, 0x00, 0x01,
    0x03, 'f', 'o', 'o', 0x00, 0x00, 0x01, 0x00, 0x01,
    0xC0, 0x0C, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x04, 'r', 'o', 'o', 't', 0x04, 'a', 'r', 'p', 'a', 0x00,
    0xC0, 0x0C, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x08, 0x04, 0x0A, 0x00, 0x00, 0x01
};

typedef struct st_qname_test_line_t {
    uint8_t * packet;
    size_t length;
    uint32_t nb_queries;
    uint32_t q_class;
    uint32_t q_type;
    uint32_t qr_start;
    uint32_t an_start;
    uint32_t ns_start;
    bool name_cmp;
    bool is_minimized;
} qname_test_line_t;

static const qname_test_line_t qname_test_case[] = {
    { p1, sizeof(p1), 1, 1, 1, 0x0C, 0, 0x21, false, false },
    { p2, sizeof(p2), 1, 1, 1, 0x0C, 0, 0x21, false, false },
    { p3, sizeof(p3), 1, 1, 1, 0x0C,  0x21, 0, true, true },
    { p4, sizeof(p4), 1, 1, 1, 0x0C, 0x1D, 0, true, true },
    { p5, sizeof(p5), 1, 1, 1, 0x0C, 0x1D, 0, true, true },
    { p5, sizeof(p6), 1, 1, 1, 0x0C, 0x1D, 0, true, true },
    { p6, sizeof(p6), 1, 1, 1, 0x0C, 0x1D, 0, true, true },
    { p7, sizeof(p7), 1, 1, 1, 0x0C, 0x1D, 0, true, true },
    { p8, sizeof(p8), 1, 1, 2, 0x0C, 0x1D, 0, true, true },
    { p9, sizeof(p9), 1, 1, 1, 0x0C, 0, 0x1D, true, true },
    { p10, sizeof(p10), 1, 1, 1, 0x0C, 0, 0x15, true, true },
    { p11, sizeof(p11), 2, 1, 1, 0x0C, 0, 0x1E, true, false },
};

static const size_t nb_qname_test_cases = sizeof(qname_test_case) / sizeof(qname_test_line_t);

CmpNameTest::CmpNameTest()
{
}

CmpNameTest::~CmpNameTest()
{
}

bool CmpNameTest::DoTest()
{
    bool ret = true;

    for (size_t i = 0; i < nb_qname_test_cases; i++) {
        uint32_t n2 = (qname_test_case[i].an_start == 0) ? qname_test_case[i].ns_start : qname_test_case[i].an_start;
        bool x = DnsStats::CompareDnsName(qname_test_case[i].packet,
            (uint32_t)qname_test_case[i].length, qname_test_case[i].qr_start, n2);

        if (x != qname_test_case[i].name_cmp) {
            TEST_LOG("Comparison case %d fails, returns %s instead of %s\n", (int)i,
                (x)?"true":"false", (qname_test_case[i].name_cmp) ? "true" : "false");
            ret = false;
        }
    }
    return ret;
}


QNameTest::QNameTest()
{
}


QNameTest::~QNameTest()
{
}

bool QNameTest::DoTest()
{
    bool ret = true;

    for (size_t i = 0; i < nb_qname_test_cases; i++) {
        bool x = DnsStats::IsQNameMinimized(
            qname_test_case[i].nb_queries, qname_test_case[i].q_class, qname_test_case[i].q_type,
            qname_test_case[i].packet, (uint32_t)qname_test_case[i].length, qname_test_case[i].qr_start,
            qname_test_case[i].packet, (uint32_t)qname_test_case[i].length, 
            (qname_test_case[i].an_start ==0)?qname_test_case[i].ns_start: qname_test_case[i].an_start);

        if (x != qname_test_case[i].is_minimized) {
            TEST_LOG("Is QName case %d fails, returns %s instead of %s\n", (int)i,
                (x) ? "true" : "false", (qname_test_case[i].is_minimized) ? "true" : "false");
            ret = false;
        }
    }
    return ret;
}