from importlib.resources import path
from conans import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps

class BuildWithConan(ConanFile):
	settings = "os", "compiler", "build_type", "arch"
	requires = "gtest/cci.20210126"
	generators = "CMakeDeps", "CMakeToolchain"

	def imports(self):
		self.copy("*.dll", dst="bin", src="bin") # From bin to bin
		self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin
	
	def generate(self):
		tc = CMakeToolchain(self)
		tc.generator = "Ninja"
		tc.generate()
		deps = CMakeDeps(self)
		deps.generate()

	def build(self):
		cmake = CMake(self)
		cmake.configure()
		cmake.build(target="format_project")
		cmake.build(target="run_clang_tidy")
		cmake.build(target="run_cppcheck")
		cmake.build(target="run_tests")
		cmake.build()
		cmake.install()