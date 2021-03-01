from conans import ConanFile, tools, Meson
import os

class ConanFileToolsTest(ConanFile):
    name = 'ChatApp'
    version = '0.0.1'
    generators = 'pkg_config'
    requires = [
            'fmt/7.1.3',
            'openssl/1.1.1j',
            'cpr/1.5.2',
            'websocketpp/0.8.2',
            'asio/1.18.1',
            'opus/1.3.1']
    settings = 'os', 'compiler', 'build_type'

    def build(self):
        meson = Meson(self)
        meson.configure(build_folder='build')
        meson.build()
