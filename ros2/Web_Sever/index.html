from flask import Flask, render_template, jsonify
import json
import os

JSON_PATH = os.environ.get("GNSS_JSON_PATH", "/tmp/gnss_data.json")

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/position')
def get_position():
    try:
        with open(JSON_PATH, 'r') as f:
            data = json.load(f)
        return jsonify(data)
    except FileNotFoundError:
        return jsonify({"lat": 0.0, "lon": 0.0, "alt": 0.0, "timestamp": "No data"})
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
