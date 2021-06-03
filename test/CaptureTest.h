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

#ifndef CAPTURE_TEST_H
#define CAPTURE_TEST_H

#include "ithi_test_class.h"

#if __cplusplus < 199711L
#ifndef override
#define override 
#endif
#endif

class CaptureTest: public ithi_test_class
{
public:
    CaptureTest();
    ~CaptureTest();
    bool DoTest() override;
};

class CaptureCborTest : public ithi_test_class
{
public:
    CaptureCborTest();
    ~CaptureCborTest();
    bool DoTest() override;
};
class CaptureNxCacheTest : public ithi_test_class
{
public:
    CaptureNxCacheTest();
    ~CaptureNxCacheTest();
    bool DoTest() override;
};

#ifdef PRIVACY_CONSCIOUS
class CaptureNamesTest : public ithi_test_class
{
public:
    CaptureNamesTest();
    ~CaptureNamesTest();
    bool DoOneTest(char const* name_debug, char const* name_ref, bool addNamesToReport);
    bool DoTest() override;
};

class CaptureQueriedNamesTest : public ithi_test_class
{
public:
    CaptureQueriedNamesTest();
    ~CaptureQueriedNamesTest();
    bool DoTest() override;
};

class CompressedNamesTest : public ithi_test_class
{
public:
    CompressedNamesTest();
    ~CompressedNamesTest();
    bool DoTest() override;
    static bool RemoveGz(char const* file_name);
    static bool Decompress(char const* file_name);
};

class CaptureAddressesTest : public ithi_test_class
{
public:
    CaptureAddressesTest();
    ~CaptureAddressesTest();
    bool DoTest() override;
};

class CompressedAddressesTest : public ithi_test_class
{
public:
    CompressedAddressesTest();
    ~CompressedAddressesTest();
    bool DoTest() override;
};

#endif

#endif /* CAPTURE_TEST_H */
