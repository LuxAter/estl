# -*- coding: utf-8 -*-
# -- General configuration ------------------------------------------------
extensions = [
    'sphinx.ext.coverage', 'sphinx.ext.imgmath', 'sphinx.ext.githubpages',
    'breathe', 'sphinx.ext.autosummary'
]

breathe_projects = {"Estl": "../doxygen/xml/"}
breathe_default_project = "Estl"

templates_path = ['_templates']

source_suffix = ['.rst', '.md']

master_doc = 'index'

project = u'Estl'
copyright = u'2017, Arden Rasmussen'
author = u'Arden Rasmussen'

version = u'0.0'
release = u'0.0'

language = None

exclude_patterns = []

pygments_style = 'sphinx'

todo_include_todos = False

# -- Options for HTML output ----------------------------------------------

#  import sphinx_rtd_theme
#  html_theme = "sphinx_rtd_theme"
#  html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]

import sphinx_bootstrap_theme
html_theme = 'bootstrap'
html_theme_path = sphinx_bootstrap_theme.get_html_theme_path()

html_show_sourcelink = True

html_show_sphinx = False

# (Optional) Logo. Should be small enough to fit the navbar (ideally 24x24).
# Path should be relative to the ``_static`` files directory.
#  html_logo = "my_logo.png"

# Theme options are theme-specific and customize the look and feel of a
# theme further.
html_theme_options = {
    'navbar_sidebarrel': False,
    'navbar_pagenav': True,
    'navbar_pagenav_name': "Page",
    'navbar_links': [("API", "api/api_index"), ("Examples", "examples_idex")],
    'globaltoc_depth': -1,
    'globaltoc_includehidden': "true",
    'navbar_class': "navbar",
    'navbar_fixed_top': "true",
    'source_link_position': "footer",
    'bootswatch_theme': "united",
    'bootstrap_version': "3",
}
# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

# Custom sidebar templates, must be a dictionary that maps document names
# to template names.
#
# This is required for the alabaster theme
# refs: http://alabaster.readthedocs.io/en/latest/installation.html#sidebars
#  html_sidebars = {
#  '**': [
#  'about.html',
#  'navigation.html',
#  'relations.html',  # needs 'show_related': True theme option to display
#  'searchbox.html',
#  'donate.html',
#  ]
#  }

# -- Options for HTMLHelp output ------------------------------------------

# Output file base name for HTML help builder.
htmlhelp_basename = 'Estldoc'

# -- Options for LaTeX output ---------------------------------------------

latex_elements = {
    # The paper size ('letterpaper' or 'a4paper').
    #
    # 'papersize': 'letterpaper',

    # The font size ('10pt', '11pt' or '12pt').
    #
    # 'pointsize': '10pt',

    # Additional stuff for the LaTeX preamble.
    #
    # 'preamble': '',

    # Latex figure (float) alignment
    #
    # 'figure_align': 'htbp',
}

# Grouping the document tree into LaTeX files. List of tuples
# (source start file, target name, title,
#  author, documentclass [howto, manual, or own class]).
latex_documents = [
    (master_doc, 'Estl.tex', u'Estl Documentation', u'project_author',
     'manual'),
]

# -- Options for manual page output ---------------------------------------

# One entry per manual page. List of tuples
# (source start file, name, description, authors, manual section).
man_pages = [(master_doc, 'estl', u'Estl Documentation', [author], 1)]

# -- Options for Texinfo output -------------------------------------------

# Grouping the document tree into Texinfo files. List of tuples
# (source start file, target name, title, author,
#  dir menu entry, description, category)
texinfo_documents = [
    (master_doc, 'Estl', u'Form Documentation', author, 'Estl',
     'Extended standard template library.', 'Miscellaneous'),
]

# -- Options for Epub output ----------------------------------------------

# Bibliographic Dublin Core info.
epub_title = project
epub_author = author
epub_publisher = author
epub_copyright = copyright

# The unique identifier of the text. This can be a ISBN number
# or the project homepage.
#
# epub_identifier = ''

# A unique identification for the text.
#
# epub_uid = ''

# A list of files that should not be packed into the epub file.
epub_exclude_files = ['search.html']
