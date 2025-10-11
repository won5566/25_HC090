#!/usr/bin/env python3
import json
import os
from datetime import datetime, timezone

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy
from sensor_msgs.msg import NavSatFix

JSON_PATH = os.environ.get("GNSS_JSON_PATH", "/tmp/gnss_data.json")

class GnssToJson(Node):
    def __init__(self):
        super().__init__("gnss_to_json")
        qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=10,
            durability=DurabilityPolicy.VOLATILE,
        )
        topic = self.declare_parameter("topic", "/fix").get_parameter_value().string_value or "/fix"
        self.sub = self.create_subscription(NavSatFix, topic, self.cb_fix, qos)
        self.get_logger().info(f"Subscribed to {topic}; writing JSON to {JSON_PATH}")

    def cb_fix(self, msg: NavSatFix):
        data = {
            "lat": msg.latitude,
            "lon": msg.longitude,
            "alt": msg.altitude,
            "status": getattr(msg.status, "status", 0),
            "service": getattr(msg.status, "service", 0),
            "timestamp": datetime.now(timezone.utc).isoformat()
        }
        try:
            os.makedirs(os.path.dirname(JSON_PATH), exist_ok=True)
            tmp_path = JSON_PATH + ".tmp"
            with open(tmp_path, "w") as f:
                json.dump(data, f)
            os.replace(tmp_path, JSON_PATH)
        except Exception as e:
            self.get_logger().error(f"Failed to write {JSON_PATH}: {e}")

def main(args=None):
    rclpy.init(args=args)
    node = GnssToJson()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == "__main__":
    main()


