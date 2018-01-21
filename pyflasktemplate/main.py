#!/usr/bin/env python
#
# A simple flask Hello World application.
#
import flask


app = flask.Flask(__name__)


@app.route("/")
def index():
    return "Hello World!"


def main():
    host = '0.0.0.0'
    port = 8080
    app.run(host=host, port=port)


if __name__ == '__main__':
    main()
