// Copyright (c) 2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <string>

#include "version.h"

// Name of client reported in the 'version' message. Report the same name
// for both bitcoind and bitcoin-qt, to make it harder for attackers to
// target servers or GUI users specifically.
const std::string CLIENT_NAME("Nicecoin");

// Client version number
#define CLIENT_VERSION_SUFFIX   ""


// The following part of the code determines the CLIENT_BUILD variable.
// Several mechanisms are used for this:
// * first, if HAVE_BUILD_INFO is defined, include build.h, a file that is
//   generated by the build environment, possibly containing the output
//   of git-describe in a macro called BUILD_DESC
// * secondly, if this is an exported version of the code, GIT_ARCHIVE will
//   be defined (automatically using the export-subst git attribute), and
//   GIT_NICIT will contain the commit id.
// * then, three options exist for determining CLIENT_BUILD:
//   * if BUILD_DESC is defined, use that literally (output of git-describe)
//   * if not, but GIT_NICIT is defined, use v[maj].[min].[rev].[build]-g[commit]
//   * otherwise, use v[maj].[min].[rev].[build]-unk
// finally CLIENT_VERSION_SUFFIX is added

// First, include build.h if requested
#ifdef HAVE_BUILD_INFO
#    include "build.h"
#endif

// git will put "#define GIT_ARCHIVE 1" on the next line inside archives. 
#define GIT_ARCHIVE 1
#ifdef GIT_ARCHIVE
#    define GIT_NICIT_ID ""
#    define GIT_NICIT_DATE "July-2014"
#endif

#define BUILD_DESC_FROM_NICIT(maj,min,rev,build,commit) \
    "v" DO_STRINGIZE(maj) "." DO_STRINGIZE(min) "." DO_STRINGIZE(rev) "." DO_STRINGIZE(build) "" commit

#define BUILD_DESC_FROM_UNKNOWN(maj,min,rev,build) \
    "v" DO_STRINGIZE(maj) "." DO_STRINGIZE(min) "." DO_STRINGIZE(rev) "." DO_STRINGIZE(build) ""

#ifndef BUILD_DESC
#    ifdef GIT_NICIT_ID
#        define BUILD_DESC BUILD_DESC_FROM_NICIT(DISPLAY_VERSION_MAJOR, DISPLAY_VERSION_MINOR, DISPLAY_VERSION_REVISION, DISPLAY_VERSION_BUILD, GIT_NICIT_ID)
#    else
#        define BUILD_DESC BUILD_DESC_FROM_UNKNOWN(DISPLAY_VERSION_MAJOR, DISPLAY_VERSION_MINOR, DISPLAY_VERSION_REVISION, DISPLAY_VERSION_BUILD)
#    endif
#endif

#ifndef BUILD_DATE
#    ifdef GIT_NICIT_DATE
#        define BUILD_DATE GIT_NICIT_DATE
#    else
#        define BUILD_DATE __DATE__ ", " __TIME__
#    endif
#endif

const std::string CLIENT_BUILD(BUILD_DESC CLIENT_VERSION_SUFFIX);
const std::string CLIENT_DATE(BUILD_DATE);
