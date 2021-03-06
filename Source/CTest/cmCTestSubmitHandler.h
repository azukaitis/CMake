/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#ifndef cmCTestSubmitHandler_h
#define cmCTestSubmitHandler_h

#include "cmConfigure.h" // IWYU pragma: keep

#include "cmCTest.h"
#include "cmCTestGenericHandler.h"

#include <iosfwd>
#include <set>
#include <string>
#include <vector>

/** \class cmCTestSubmitHandler
 * \brief Helper class for CTest
 *
 * Submit testing results
 *
 */
class cmCTestSubmitHandler : public cmCTestGenericHandler
{
public:
  typedef cmCTestGenericHandler Superclass;

  cmCTestSubmitHandler();
  ~cmCTestSubmitHandler() override { this->LogFile = nullptr; }

  /*
   * The main entry point for this class
   */
  int ProcessHandler() override;

  void Initialize() override;

  /** Specify a set of parts (by name) to submit.  */
  void SelectParts(std::set<cmCTest::Part> const& parts);

  /** Specify a set of files to submit.  */
  void SelectFiles(cmCTest::SetOfStrings const& files);

  // handle the cdash file upload protocol
  int HandleCDashUploadFile(std::string const& file, std::string const& type);

  void SetHttpHeaders(std::vector<std::string> const& v)
  {
    this->HttpHeaders = v;
  }

  void ConstructCDashURL(std::string& dropMethod, std::string& url);

private:
  void SetLogFile(std::ostream* ost) { this->LogFile = ost; }

  /**
   * Submit file using various ways
   */
  bool SubmitUsingHTTP(const std::string& localprefix,
                       const std::vector<std::string>& files,
                       const std::string& remoteprefix,
                       const std::string& url);

  typedef std::vector<char> cmCTestSubmitHandlerVectorOfChar;

  void ParseResponse(cmCTestSubmitHandlerVectorOfChar chunk);

  std::string GetSubmitResultsPrefix();

  class ResponseParser;

  std::string HTTPProxy;
  int HTTPProxyType;
  std::string HTTPProxyAuth;
  std::ostream* LogFile;
  bool SubmitPart[cmCTest::PartCount];
  bool HasWarnings;
  bool HasErrors;
  cmCTest::SetOfStrings Files;
  std::vector<std::string> HttpHeaders;
};

#endif
