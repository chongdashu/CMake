/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#ifndef cmQtAutoGenerators_h
#define cmQtAutoGenerators_h

#include <cmConfigure.h> // IWYU pragma: keep
#include <cmFilePathChecksum.h>
#include <cmsys/RegularExpression.hxx>

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

class cmMakefile;

class cmQtAutoGenerators
{
public:
  cmQtAutoGenerators();
  bool Run(const std::string& targetDirectory, const std::string& config);

private:
  bool ReadAutogenInfoFile(cmMakefile* makefile,
                           const std::string& targetDirectory,
                           const std::string& config);
  void ReadOldMocDefinitionsFile(cmMakefile* makefile,
                                 const std::string& targetDirectory);
  bool WriteOldMocDefinitionsFile(const std::string& targetDirectory);

  std::string MakeCompileSettingsString(cmMakefile* makefile);

  bool RunAutogen(cmMakefile* makefile);

  bool GenerateMocFiles(
    const std::map<std::string, std::string>& includedMocs,
    const std::map<std::string, std::string>& notIncludedMocs);
  bool GenerateMoc(const std::string& sourceFile,
                   const std::string& mocFileName,
                   const std::string& subDirPrefix);

  bool GenerateUiFiles(
    const std::map<std::string, std::vector<std::string> >& includedUis);
  bool GenerateUi(const std::string& realName, const std::string& uiInputFile,
                  const std::string& uiOutputFile);

  bool GenerateQrcFiles();
  bool GenerateQrc(const std::string& qrcInputFile,
                   const std::string& qrcOutputFile, bool unique_n);

  bool ParseSourceFile(
    const std::string& absFilename,
    const std::vector<std::string>& headerExtensions,
    std::map<std::string, std::string>& includedMocs,
    std::map<std::string, std::vector<std::string> >& includedUis,
    bool relaxed);
  void SearchHeadersForSourceFile(
    const std::string& absFilename,
    const std::vector<std::string>& headerExtensions,
    std::set<std::string>& absHeadersMoc,
    std::set<std::string>& absHeadersUic);

  void ParseHeaders(
    const std::set<std::string>& absHeadersMoc,
    const std::set<std::string>& absHeadersUic,
    const std::map<std::string, std::string>& includedMocs,
    std::map<std::string, std::string>& notIncludedMocs,
    std::map<std::string, std::vector<std::string> >& includedUis);

  bool requiresMocing(const std::string& text, std::string& macroName);

  void ParseContentForUic(
    const std::string& fileName, const std::string& contentsString,
    std::map<std::string, std::vector<std::string> >& includedUis);

  bool ParseContentForMoc(const std::string& absFilename,
                          const std::string& contentsString,
                          const std::vector<std::string>& headerExtensions,
                          std::map<std::string, std::string>& includedMocs,
                          bool relaxed);

  void ParseForUic(
    const std::string& fileName,
    std::map<std::string, std::vector<std::string> >& includedUis);

  void Init();

  bool MocSkipTest(const std::string& absFilename);
  bool UicSkipTest(const std::string& absFilename);

  bool NameCollisionTest(const std::map<std::string, std::string>& genFiles,
                         std::multimap<std::string, std::string>& collisions);

  void LogErrorNameCollision(
    const std::string& message,
    const std::multimap<std::string, std::string>& collisions);
  void LogBold(const std::string& message);
  void LogInfo(const std::string& message);
  void LogWarning(const std::string& message);
  void LogError(const std::string& message);
  void LogCommand(const std::vector<std::string>& command);

  bool MakeParentDirectory(const std::string& filename);

  std::string JoinExts(const std::vector<std::string>& lst);

  static void MergeUicOptions(std::vector<std::string>& opts,
                              const std::vector<std::string>& fileOpts,
                              bool isQt5);

  bool InputFilesNewerThanQrc(const std::string& qrcFile,
                              const std::string& rccOutput);

  // - Target names
  std::string OriginTargetName;
  std::string AutogenTargetName;
  // - Directories
  std::string ProjectSourceDir;
  std::string ProjectBinaryDir;
  std::string CurrentSourceDir;
  std::string CurrentBinaryDir;
  std::string AutogenBuildSubDir;
  // - Qt environment
  std::string QtMajorVersion;
  std::string MocExecutable;
  std::string UicExecutable;
  std::string RccExecutable;
  // - File lists
  std::vector<std::string> Sources;
  std::vector<std::string> Headers;
  // - Moc
  std::vector<std::string> SkipMoc;
  std::string MocCompileDefinitionsStr;
  std::string MocIncludesStr;
  std::string MocOptionsStr;
  std::string OutMocCppFilenameRel;
  std::string OutMocCppFilenameAbs;
  std::list<std::string> MocIncludes;
  std::list<std::string> MocDefinitions;
  std::vector<std::string> MocOptions;
  // - Uic
  std::vector<std::string> SkipUic;
  std::vector<std::string> UicTargetOptions;
  std::map<std::string, std::string> UicOptions;
  // - Rcc
  std::vector<std::string> RccSources;
  std::map<std::string, std::string> RccOptions;
  std::map<std::string, std::vector<std::string> > RccInputs;
  // - Settings
  std::string CurrentCompileSettingsStr;
  std::string OldCompileSettingsStr;
  // - Utility
  cmFilePathChecksum fpathCheckSum;
  cmsys::RegularExpression RegExpQObject;
  cmsys::RegularExpression RegExpQGadget;
  cmsys::RegularExpression RegExpMocInclude;
  cmsys::RegularExpression RegExpUicInclude;
  // - Flags
  bool IncludeProjectDirsBefore;
  bool Verbose;
  bool ColorOutput;
  bool RunMocFailed;
  bool RunUicFailed;
  bool RunRccFailed;
  bool GenerateAll;
  bool MocRelaxedMode;
};

#endif
