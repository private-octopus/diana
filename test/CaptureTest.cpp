/*
* Author: Christian Huitema
* Copyright (c) 2017, Private Octopus, Inc.
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

#include <stdio.h>
#include "DnsStats.h"
#include "pcap_reader.h"
#include "MetricTest.h"
#include "ithi_test_class.h"
#include "CaptureTest.h"

#ifdef _WINDOWS
#ifndef _WINDOWS64
static char const * pcap_input_test = "..\\data\\tiny-capture.pcap";
static char const * pcap_test_output = "..\\data\\tiny-capture-tcp.csv";
static char const* cbor_input_test = "..\\cdns\\test\\data\\gold.cbor";
static char const* cbor_test_output = "..\\..\\data\\capture_gold.csv";
static char const* pcap_test_output_nx = "..\\data\\tiny-capture-nx.csv";
#else
static char const * pcap_input_test = "..\\..\\data\\tiny-capture.pcap";
static char const * pcap_test_output = "..\\..\\data\\tiny-capture-tcp.csv";
static char const* cbor_input_test = "..\\..\\cdns\\test\\data\\gold.cbor";
static char const* cbor_test_output = "..\\..\\data\\capture_gold.csv";
static char const* pcap_test_output_nx = "..\\..\\data\\tiny-capture-nx.csv";
#endif
#else
static char const * pcap_input_test = "data/tiny-capture.pcap";
static char const * pcap_test_output = "data/tiny-capture-tcp.csv";
static char const* cbor_input_test = "cdns/test/data/gold.cbor";
static char const* cbor_test_output = "data/capture_gold.csv";
static char const* pcap_test_output_nx = "data/tiny-capture-nx.csv";
#endif
static char const* pcap_test_debug = "tiny-capture-out.csv";
static char const* cbor_test_debug = "gold-cbor-out.csv";
static char const* pcap_test_debug_nx = "tiny-capture-nx.csv";

#ifdef PRIVACY_CONSCIOUS
#ifdef _WINDOWS
#ifndef _WINDOWS64
static char const* pcap_names_output = "..\\data\\tiny-capture-names.csv";
static char const* pcap_queried_names_output = "..\\data\\tiny-capture-queried-names.csv";
static char const* pcap_addresses_output = "..\\data\\tiny-capture-addresses.csv";
#else
static char const* pcap_names_output = "..\\..\\data\\tiny-capture-names.csv";
static char const* pcap_queried_names_output = "..\\..\\data\\tiny-capture-queried-names.csv";
static char const* pcap_addresses_output = "..\\..\\data\\tiny-capture-addresses.csv";
static char const* gzip_names_output = "..\\..\\data\\tiny-compressed-names.csv";
static char const* gzip_addresses_output = "..\\..\\data\\tiny-compressed-addresses.csv";
#endif
#else
static char const* pcap_names_output = "data/tiny-capture-names.csv";
static char const* pcap_queried_names_output = "data/tiny-capture-queried-names.csv";
static char const* pcap_addresses_output = "data/tiny-capture-addresses.csv";
#endif

static char const* pcap_names_debug = "tiny-capture-names.csv";
static char const* pcap_queried_names_debug = "tiny-capture-queried-names.csv";
static char const* pcap_addresses_debug = "tiny-capture-addresses.csv";
static char const* compressed_names_debug = "tiny-gzip-names.csv";
static char const* compressed_addresses_debug = "tiny-gzip-addresses.csv";

#endif

CaptureTest::CaptureTest()
{
}


CaptureTest::~CaptureTest()
{
}

bool CaptureTest::DoTest()
{
    DnsStats capture;
    CaptureSummary cs;
    char const * list[1] = { pcap_input_test };
    bool ret = capture.LoadPcapFiles(1, list);

    if (ret)
    {
        ret = capture.ExportToCaptureSummary(&cs);

        if (ret)
        {
            CaptureSummary tcs;

            ret = tcs.Load(pcap_test_output);

            if (ret)
            {
                cs.Sort();
                tcs.Sort();

                ret = ithi_test_class::CompareCS(&cs, &tcs);

                if (!ret)
                {
                    cs.Save(pcap_test_debug);
                }
            }
        }
    }

    return ret;
}

CaptureCborTest::CaptureCborTest()
{
}


CaptureCborTest::~CaptureCborTest()
{
}

bool CaptureCborTest::DoTest()
{
    DnsStats capture;
    CaptureSummary cs;
    char const* list[1] = { cbor_input_test };
    bool ret = capture.LoadCborFiles(1, list);

    if (ret)
    {
        ret = capture.ExportToCaptureSummary(&cs);

        if (ret)
        {
            CaptureSummary tcs;

            ret = tcs.Load(cbor_test_output);

            if (ret)
            {
                cs.Sort();
                tcs.Sort();

                ret = ithi_test_class::CompareCS(&cs, &tcs);

                if (!ret)
                {
                    cs.Save(cbor_test_debug);
                }
            }
        }
    }

    return ret;
}


CaptureNxCacheTest::CaptureNxCacheTest()
{}

CaptureNxCacheTest::~CaptureNxCacheTest()
{}

bool CaptureNxCacheTest::DoTest() 
{
    DnsStats capture;
    CaptureSummary cs;
    char const* list[1] = { pcap_input_test };
    bool ret = true;

    capture.capture_cache_ratio_nx_domain = true;

    ret = capture.LoadPcapFiles(1, list);

    if (ret)
    {
        ret = capture.ExportToCaptureSummary(&cs);

        if (ret)
        {
            CaptureSummary tcs;

            ret = tcs.Load(pcap_test_output_nx);

            if (ret)
            {
                cs.Sort();
                tcs.Sort();

                ret = ithi_test_class::CompareCS(&cs, &tcs);

                if (!ret)
                {
                    cs.Save(pcap_test_debug_nx);
                }
            }
        }
    }

    return ret;
}

#ifdef PRIVACY_CONSCIOUS
CaptureNamesTest::CaptureNamesTest()
{
}

CaptureNamesTest::~CaptureNamesTest()
{
}

bool CaptureNamesTest::DoOneTest(
    char const * name_debug,
    char const * name_ref,
    bool addNamesToReport)
{
    DnsStats capture;
    CaptureSummary cs;
    char const* list[1] = { pcap_input_test };
    bool ret = true;

    capture.name_report = name_debug;
    capture.add_queried_names_to_report = addNamesToReport;
    
    ret = capture.LoadPcapFiles(1, list);

    if (ret)
    {
        ret = capture.ExportToCaptureSummary(&cs);

        if (ret)
        {
            CaptureSummary tcs;

            ret = tcs.Load(pcap_test_output);

            if (ret)
            {
                cs.Sort();
                tcs.Sort();

                ret = ithi_test_class::CompareCS(&cs, &tcs);

                if (!ret)
                {
                    cs.Save(pcap_test_debug);
                }
            }

            if (ret)
            {
                ret = MetricTest::compare_files(name_debug, name_ref);
            }
        }
    }

    return ret;
}

bool CaptureNamesTest::DoTest()
{
    return DoOneTest(pcap_names_debug, pcap_names_output, false);
}

CompressedNamesTest::CompressedNamesTest()
{
}

CompressedNamesTest::~CompressedNamesTest()
{
}

bool CompressedNamesTest::RemoveGz(char const* file_name)
{
    char command[512];
    int nbchars = 0;
    bool ret = false;
    int sys_ret;

#ifdef _WINDOWS
    nbchars = sprintf_s(command, sizeof(command), "del %s*", file_name);
#else
    nbchars = sprintf(command, "rm -f %s*", file_name);
#endif
    if (nbchars > 0) {
        sys_ret = system(command);
        if (sys_ret != 0) {
            TEST_LOG("Command <%s> returns %d\n", command, sys_ret);
        }
        else {
            ret = true;
        }
    }

    return ret;
}

bool CompressedNamesTest::Decompress(char const* file_name)
{
    char command[512];
    int nbchars = 0;
    bool ret = false;
    int sys_ret;

#ifdef _WINDOWS
    nbchars = sprintf_s(command, sizeof(command), "7z.exe x %s.gz >7z-report.txt 2>7z-errors.txt", file_name);
#else
    nbchars = sprintf(command, "gunzip -c %s.gz >%s", file_name, file_name);
#endif
    if (nbchars > 0) {
        sys_ret = system(command);
        if (sys_ret != 0) {
            TEST_LOG("Command <%s> returns %d\n", command, sys_ret);
        }
        else {
            ret = true;
        }
    }

    return ret;
}

bool CompressedNamesTest::DoTest()
{
    DnsStats capture;
    CaptureSummary cs;
    char const* list[1] = { pcap_input_test };
    bool ret = true;

    capture.name_report = compressed_names_debug;
    capture.compress_name_and_address_reports = true;

    (void)CompressedNamesTest::RemoveGz(compressed_names_debug);
    ret = capture.LoadPcapFiles(1, list);

    if (ret)
    {
        ret = capture.ExportToCaptureSummary(&cs);

        if (ret)
        {
            CaptureSummary tcs;

            ret = tcs.Load(pcap_test_output);

            if (ret)
            {
                cs.Sort();
                tcs.Sort();

                ret = ithi_test_class::CompareCS(&cs, &tcs);

                if (!ret)
                {
                    cs.Save(pcap_test_debug);
                }
            }

            if (ret) {
                ret = CompressedNamesTest::Decompress(compressed_names_debug);
            }

            if (ret)
            {
                ret = MetricTest::compare_files(compressed_names_debug, pcap_names_output);
            }
        }
    }

    return ret;
}



CaptureAddressesTest::CaptureAddressesTest()
{
}

CaptureAddressesTest::~CaptureAddressesTest()
{
}

bool CaptureAddressesTest::DoTest()
{
    DnsStats capture;
    CaptureSummary cs;
    char const* list[1] = { pcap_input_test };
    bool ret = true;

    capture.address_report = pcap_addresses_debug;
    ret = capture.LoadPcapFiles(1, list);

    if (ret)
    {
        ret = capture.ExportToCaptureSummary(&cs);

        if (ret)
        {
            CaptureSummary tcs;

            ret = tcs.Load(pcap_test_output);

            if (ret)
            {
                cs.Sort();
                tcs.Sort();

                ret = ithi_test_class::CompareCS(&cs, &tcs);

                if (!ret)
                {
                    cs.Save(pcap_test_debug);
                }
            }

            if (ret)
            {
                ret = MetricTest::compare_files(pcap_addresses_debug, pcap_addresses_output);
            }
        }
    }

    return ret;
}

CompressedAddressesTest::CompressedAddressesTest()
{
}

CompressedAddressesTest::~CompressedAddressesTest()
{
}

bool CompressedAddressesTest::DoTest()
{
    DnsStats capture;
    CaptureSummary cs;
    char const* list[1] = { pcap_input_test };
    bool ret = true;

    capture.address_report = compressed_addresses_debug;
    capture.compress_name_and_address_reports = true;
    (void)CompressedNamesTest::RemoveGz(compressed_addresses_debug);

    ret = capture.LoadPcapFiles(1, list);

    if (ret)
    {
        ret = capture.ExportToCaptureSummary(&cs);

        if (ret)
        {
            CaptureSummary tcs;

            ret = tcs.Load(pcap_test_output);

            if (ret)
            {
                cs.Sort();
                tcs.Sort();

                ret = ithi_test_class::CompareCS(&cs, &tcs);

                if (!ret)
                {
                    cs.Save(pcap_test_debug);
                }
            }

            if (ret) {
                ret = CompressedNamesTest::Decompress(compressed_addresses_debug);
            }

            if (ret)
            {
                ret = MetricTest::compare_files(compressed_addresses_debug, pcap_addresses_output);
            }
        }
    }

    return ret;
}

CaptureQueriedNamesTest::CaptureQueriedNamesTest()
{
}

CaptureQueriedNamesTest::~CaptureQueriedNamesTest()
{
}

bool CaptureQueriedNamesTest::DoTest()
{
    CaptureNamesTest ctn;

    return ctn.DoOneTest(pcap_queried_names_debug, pcap_queried_names_output, true);
}
#endif
