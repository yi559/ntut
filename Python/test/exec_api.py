import coverage
import unittest

cov = coverage.coverage(branch=True,source=['mybmi'])
cov.start()
suite = unittest.defaultTestLoader.discover("./","mybmitest.py")
unittest.TextTestRunner().run(suite)
cov.stop()
cov.save()
cov.report()
cov.html_report(directory='cov')