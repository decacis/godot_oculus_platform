# Godot Oculus Platform Documentation
This branch stores the documentation source code for the Godot Oculus Platform plugin. If you wish to contribute to the documentation, this is the place to do so!

We use [MkDocs](https://www.mkdocs.org/) and [Material for MkDocs](https://squidfunk.github.io/mkdocs-material/) so everything is markdown, but there are a couple of extensions and plugins to customize the look of the docs.

## Deploy a local version of these docs
We advise you develop locally to make sure everything works and looks good before submitting a pull request. To deploy a local version of the docs, you have to install the following packages:
```
pip install mkdocs-material mkdocs-git-revision-date-localized-plugin
```

Then run:
```
mkdocs serve
```

To see deploy the site locally. It will update everytime you change something.