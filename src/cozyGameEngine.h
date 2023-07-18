#include <cstdint>
#include <string>

#define CGE_VERSION_MAJOR 0

namespace cge
{
  class CozyGameEngine;

  constexpr uint8_t  nMouseButtons = 5;
	constexpr uint8_t  nDefaultAlpha = 0xFF;
	constexpr uint32_t nDefaultPixel = (nDefaultAlpha << 24);
	constexpr uint8_t  nTabSizeInSpaces = 2;
  enum rcode { OK = 0, FAIL = 1 };

  struct Pixel
  {
    union
    {
      uint32_t n = nDefaultPixel;
      struct { uint8_t r; uint8_t g; uint8_t b; uint8_t a; };
    };

    enum Mode {NORMAL, ALPHA, CUSTOM };

    Pixel();
    Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = nDefaultAlpha);
    Pixel(uint32_t color);
    Pixel(std::string hexcode, uint8_t alpha = nDefaultAlpha);
    Pixel& operator = (const Pixel& v) = default;
		bool   operator ==(const Pixel& p) const;
		bool   operator !=(const Pixel& p) const;
		Pixel  operator * (const float i) const;
		Pixel  operator / (const float i) const;
		Pixel& operator *=(const float i);
		Pixel& operator /=(const float i);
		Pixel  operator + (const Pixel& p) const;
		Pixel  operator - (const Pixel& p) const;
		Pixel& operator +=(const Pixel& p);
		Pixel& operator -=(const Pixel& p);
		Pixel  inv() const;
  };

  // O------------------------------------------------------------------------------O
	// | USEFUL CONSTANTS                                                             |
	// O------------------------------------------------------------------------------O
	static const Pixel
		GREY(192, 192, 192), DARK_GREY(128, 128, 128), VERY_DARK_GREY(64, 64, 64),
		RED(255, 0, 0), DARK_RED(128, 0, 0), VERY_DARK_RED(64, 0, 0),
		YELLOW(255, 255, 0), DARK_YELLOW(128, 128, 0), VERY_DARK_YELLOW(64, 64, 0),
		GREEN(0, 255, 0), DARK_GREEN(0, 128, 0), VERY_DARK_GREEN(0, 64, 0),
		CYAN(0, 255, 255), DARK_CYAN(0, 128, 128), VERY_DARK_CYAN(0, 64, 64),
		BLUE(0, 0, 255), DARK_BLUE(0, 0, 128), VERY_DARK_BLUE(0, 0, 64),
		MAGENTA(255, 0, 255), DARK_MAGENTA(128, 0, 128), VERY_DARK_MAGENTA(64, 0, 64),
		WHITE(255, 255, 255), BLACK(0, 0, 0), BLANK(0, 0, 0, 0);
  
  
  enum Key
	{
		NONE,
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		UP, DOWN, LEFT, RIGHT,
		SPACE, TAB, SHIFT, CTRL, INS, DEL, HOME, END, PGUP, PGDN,
		BACK, ESCAPE, RETURN, ENTER, PAUSE, SCROLL,
		NP0, NP1, NP2, NP3, NP4, NP5, NP6, NP7, NP8, NP9,
		NP_MUL, NP_DIV, NP_ADD, NP_SUB, NP_DECIMAL, PERIOD,
		EQUALS, COMMA, MINUS,
		OEM_1, OEM_2, OEM_3, OEM_4, OEM_5, OEM_6, OEM_7, OEM_8,
		CAPS_LOCK, ENUM_END
	};

  namespace Mouse
	{
		static constexpr int32_t LEFT = 0;
		static constexpr int32_t RIGHT = 1;
		static constexpr int32_t MIDDLE = 2;
	};

  // O------------------------------------------------------------------------------O
	// | cge::HWButton - Represents the state of a hardware button (mouse/key)        |
	// O------------------------------------------------------------------------------O
	struct HWButton
	{
		bool bPressed = false;	// Set once during the frame the event occurs
		bool bReleased = false;	// Set once during the frame the event occurs
		bool bHeld = false;		// Set true for all frames between pressed and released events
	};


  // O------------------------------------------------------------------------------O
  // | cge::vi2d - 2D Vector (short)                                                |
  // O------------------------------------------------------------------------------O
	template <class T>
	struct v2d_generic
	{
		T x = 0;
		T y = 0;
		v2d_generic() : x(0), y(0) {}
		v2d_generic(T _x, T _y) : x(_x), y(_y) {}
		v2d_generic(const v2d_generic& v) : x(v.x), y(v.y) {}
		v2d_generic& operator=(const v2d_generic& v) = default;
		T mag() const { return T(std::sqrt(x * x + y * y)); }
		T mag2() const { return x * x + y * y; }
		v2d_generic  norm() const { T r = 1 / mag(); return v2d_generic(x * r, y * r); }
		v2d_generic  perp() const { return v2d_generic(-y, x); }
		v2d_generic  floor() const { return v2d_generic(std::floor(x), std::floor(y)); }
		v2d_generic  ceil() const { return v2d_generic(std::ceil(x), std::ceil(y)); }
		v2d_generic  max(const v2d_generic& v) const { return v2d_generic(std::max(x, v.x), std::max(y, v.y)); }
		v2d_generic  min(const v2d_generic& v) const { return v2d_generic(std::min(x, v.x), std::min(y, v.y)); }
		v2d_generic  cart() { return { std::cos(y) * x, std::sin(y) * x }; }
		v2d_generic  polar() { return { mag(), std::atan2(y, x) }; }
		T dot(const v2d_generic& rhs) const { return this->x * rhs.x + this->y * rhs.y; }
		T cross(const v2d_generic& rhs) const { return this->x * rhs.y - this->y * rhs.x; }
		v2d_generic  operator +  (const v2d_generic& rhs) const { return v2d_generic(this->x + rhs.x, this->y + rhs.y); }
		v2d_generic  operator -  (const v2d_generic& rhs) const { return v2d_generic(this->x - rhs.x, this->y - rhs.y); }
		v2d_generic  operator *  (const T& rhs)           const { return v2d_generic(this->x * rhs, this->y * rhs); }
		v2d_generic  operator *  (const v2d_generic& rhs) const { return v2d_generic(this->x * rhs.x, this->y * rhs.y); }
		v2d_generic  operator /  (const T& rhs)           const { return v2d_generic(this->x / rhs, this->y / rhs); }
		v2d_generic  operator /  (const v2d_generic& rhs) const { return v2d_generic(this->x / rhs.x, this->y / rhs.y); }
		v2d_generic& operator += (const v2d_generic& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
		v2d_generic& operator -= (const v2d_generic& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
		v2d_generic& operator *= (const T& rhs) { this->x *= rhs; this->y *= rhs; return *this; }
		v2d_generic& operator /= (const T& rhs) { this->x /= rhs; this->y /= rhs; return *this; }
		v2d_generic& operator *= (const v2d_generic& rhs) { this->x *= rhs.x; this->y *= rhs.y; return *this; }
		v2d_generic& operator /= (const v2d_generic& rhs) { this->x /= rhs.x; this->y /= rhs.y; return *this; }
		v2d_generic  operator +  () const { return { +x, +y }; }
		v2d_generic  operator -  () const { return { -x, -y }; }
		bool operator == (const v2d_generic& rhs) const { return (this->x == rhs.x && this->y == rhs.y); }
		bool operator != (const v2d_generic& rhs) const { return (this->x != rhs.x || this->y != rhs.y); }
		const std::string str() const { return std::string("(") + std::to_string(this->x) + "," + std::to_string(this->y) + ")"; }
		friend std::ostream& operator << (std::ostream& os, const v2d_generic& rhs) { os << rhs.str(); return os; }
		operator v2d_generic<int32_t>() const { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y) }; }
		operator v2d_generic<float>() const { return { static_cast<float>(this->x), static_cast<float>(this->y) }; }
		operator v2d_generic<double>() const { return { static_cast<double>(this->x), static_cast<double>(this->y) }; }
	};

	// Note: joshinils has some good suggestions here, but they are complicated to implement at this moment, 
	// however they will appear in a future version of PGE
	template<class T> inline v2d_generic<T> operator * (const float& lhs, const v2d_generic<T>& rhs)
	{ return v2d_generic<T>((T)(lhs * (float)rhs.x), (T)(lhs * (float)rhs.y)); }
	template<class T> inline v2d_generic<T> operator * (const double& lhs, const v2d_generic<T>& rhs)
	{ return v2d_generic<T>((T)(lhs * (double)rhs.x), (T)(lhs * (double)rhs.y)); }
	template<class T> inline v2d_generic<T> operator * (const int& lhs, const v2d_generic<T>& rhs)
	{ return v2d_generic<T>((T)(lhs * (int)rhs.x), (T)(lhs * (int)rhs.y)); }
	template<class T> inline v2d_generic<T> operator / (const float& lhs, const v2d_generic<T>& rhs)
	{ return v2d_generic<T>((T)(lhs / (float)rhs.x), (T)(lhs / (float)rhs.y)); }
	template<class T> inline v2d_generic<T> operator / (const double& lhs, const v2d_generic<T>& rhs)
	{ return v2d_generic<T>((T)(lhs / (double)rhs.x), (T)(lhs / (double)rhs.y)); }
	template<class T> inline v2d_generic<T> operator / (const int& lhs, const v2d_generic<T>& rhs)
	{ return v2d_generic<T>((T)(lhs / (int)rhs.x), (T)(lhs / (int)rhs.y)); }

	// To stop dandistine crying...
	template<class T, class U> inline bool operator < (const v2d_generic<T>& lhs, const v2d_generic<U>& rhs)
	{ return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x); }
	template<class T, class U> inline bool operator > (const v2d_generic<T>& lhs, const v2d_generic<U>& rhs)
	{ return lhs.y > rhs.y || (lhs.y == rhs.y && lhs.x > rhs.x); }

	typedef v2d_generic<int32_t> vi2d;
	typedef v2d_generic<uint32_t> vu2d;
	typedef v2d_generic<float> vf2d;
	typedef v2d_generic<double> vd2d;

  class Renderer
	{
	public:
		virtual ~Renderer() = default;
		virtual void       PrepareDevice() = 0;
		virtual cge::rcode CreateDevice(std::vector<void*> params, bool bFullScreen, bool bVSYNC) = 0;
		virtual cge::rcode DestroyDevice() = 0;
		virtual void       DisplayFrame() = 0;
		virtual void       PrepareDrawing() = 0;
		virtual void       ClearBuffer(cge::Pixel p, bool bDepth) = 0;
		static cge::CozyGameEngine* ptrCGE;
	};

  class Platform
	{
	public:
		virtual ~Platform() = default;
		virtual cge::rcode ApplicationStartUp() = 0;
		virtual cge::rcode ApplicationCleanUp() = 0;
		virtual cge::rcode ThreadStartUp() = 0;
		virtual cge::rcode ThreadCleanUp() = 0;
		virtual cge::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const cge::vi2d& vViewPos, const cge::vi2d& vViewSize) = 0;
		virtual cge::rcode CreateWindowPane(const cge::vi2d& vWindowPos, cge::vi2d& vWindowSize, bool bFullScreen) = 0;
		virtual cge::rcode SetWindowTitle(const std::string& s) = 0;
		virtual cge::rcode StartSystemEventLoop() = 0;
		virtual cge::rcode HandleSystemEvent() = 0;
		static cge::CozyGameEngine* ptrCGE;
	};

  static std::unique_ptr<Renderer> renderer;
	static std::unique_ptr<Platform> platform;

  class CozyGameEngine
  {
  public:
    CozyGameEngine();
    virtual ~CozyGameEngine();
  public:
    cge::rcode Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h, bool full_screen = false, bool vsync = false);
    cge::rcode Start();


  public: // User Override Interfaces
    // Called once on application startup, use to load your resources
    virtual bool OnUserCreate();
    // Called every frame, and provides you with a time per frame value
    virtual bool OnUserUpdate(float fElapsedTime);
    // Called once on application termination, so you can be one clean coder
    virtual bool OnUserDestroy();

  public: // Hardware Interfaces
    bool IsFocused();

    HWButton GetKey(Key k) const;
    HWButton GetMouse(int32_t b) const;
    int32_t GetMouseX() const;
    int32_t GetMouseY() const;


  public: // Utility
		// Returns the width of the screen in "pixels"
		int32_t ScreenWidth() const;
		// Returns the height of the screen in "pixels"
		int32_t ScreenHeight() const;
    // Gets the current Frames Per Second
		uint32_t GetFPS() const;
		// Gets last update of elapsed time
		float GetElapsedTime() const;
    // Gets Actual Window size
		const cge::vi2d& GetWindowSize() const;
		// Gets pixel scale
		const cge::vi2d& GetPixelSize() const;
		// Gets actual pixel scale
		const cge::vi2d& GetScreenPixelSize() const;
  
  public: // Draw Routines
    // Draws a single pixel at x,y
    virtual bool Draw(int32_t x, int32_t y, Pixel p = cge::WHITE);
    // Draws a line from (x1,y1) to (x2,y2)
		void DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Pixel p = cge::WHITE, uint32_t pattern = 0xFFFFFFFF);
		void DrawLine(const cge::vi2d& pos1, const cge::vi2d& pos2, Pixel p = cge::WHITE, uint32_t pattern = 0xFFFFFFFF);
		// Draws a circle located at (x,y) with radius
		void DrawCircle(int32_t x, int32_t y, int32_t radius, Pixel p = cge::WHITE, uint8_t mask = 0xFF);
		void DrawCircle(const cge::vi2d& pos, int32_t radius, Pixel p = cge::WHITE, uint8_t mask = 0xFF);
		// Fills a circle located at (x,y) with radius
		void FillCircle(int32_t x, int32_t y, int32_t radius, Pixel p = cge::WHITE);
		void FillCircle(const cge::vi2d& pos, int32_t radius, Pixel p = cge::WHITE);
		// Draws a rectangle at (x,y) to (x+w,y+h)
		void DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p = cge::WHITE);
		void DrawRect(const cge::vi2d& pos, const cge::vi2d& size, Pixel p = cge::WHITE);
		// Fills a rectangle at (x,y) to (x+w,y+h)
		void FillRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p = cge::WHITE);
		void FillRect(const cge::vi2d& pos, const cge::vi2d& size, Pixel p = cge::WHITE);
		// Draws a triangle between points (x1,y1), (x2,y2) and (x3,y3)
		void DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p = cge::WHITE);
		void DrawTriangle(const cge::vi2d& pos1, const cge::vi2d& pos2, const cge::vi2d& pos3, Pixel p = cge::WHITE);
		// Flat fills a triangle between points (x1,y1), (x2,y2) and (x3,y3)
		void FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p = cge::WHITE);
		void FillTriangle(const cge::vi2d& pos1, const cge::vi2d& pos2, const cge::vi2d& pos3, Pixel p = cge::WHITE);
  
  public: // Branding
		std::string AppName;


  private: // Inner mysterious workings
		Pixel::Mode	nPixelMode = Pixel::NORMAL;
		float		fBlendFactor = 1.0f;
		cge::vi2d	vScreenSize = { 256, 240 };
		cge::vf2d	vInvScreenSize = { 1.0f / 256.0f, 1.0f / 240.0f };
		cge::vi2d	vPixelSize = { 4, 4 };
		cge::vi2d   vScreenPixelSize = { 4, 4 };
		cge::vi2d	vMousePos = { 0, 0 };
		int32_t		nMouseWheelDelta = 0;
		cge::vi2d	vMousePosCache = { 0, 0 };
		cge::vi2d   vMouseWindowPos = { 0, 0 };
		int32_t		nMouseWheelDeltaCache = 0;
		cge::vi2d	vWindowSize = { 0, 0 };
		cge::vi2d	vViewPos = { 0, 0 };
		cge::vi2d	vViewSize = { 0,0 };
		bool		bFullScreen = false;
		cge::vf2d	vPixel = { 1.0f, 1.0f };
		bool		bHasInputFocus = false;
		bool		bHasMouseFocus = false;
		bool		bEnableVSYNC = false;
		float		fFrameTimer = 1.0f;
		float		fLastElapsed = 0.0f;
		int			nFrameCount = 0;
		uint8_t		nTargetLayer = 0;
		uint32_t	nLastFPS = 0;
		bool      bPixelCohesion = false;
		std::function<cge::Pixel(const int x, const int y, const cge::Pixel&, const cge::Pixel&)> funcPixelMode;
		std::chrono::time_point<std::chrono::system_clock> m_tp1, m_tp2;
		std::vector<cge::vi2d> vFontSpacing;

		// State of keyboard		
		bool		pKeyNewState[256] = { 0 };
		bool		pKeyOldState[256] = { 0 };
		HWButton	pKeyboardState[256] = { 0 };

		// State of mouse
		bool		pMouseNewState[nMouseButtons] = { 0 };
		bool		pMouseOldState[nMouseButtons] = { 0 };
		HWButton	pMouseState[nMouseButtons] = { 0 };

    // The main engine thread
		void EngineThread();

    // If anything sets this flag to false, the engine
		// "should" shut down gracefully
		static std::atomic<bool> bAtomActive;

  public:
		// "Break In" Functions
		void cge_UpdateMouse(int32_t x, int32_t y);
		void cge_UpdateMouseWheel(int32_t delta);
		void cge_UpdateWindowSize(int32_t x, int32_t y);
		void cge_UpdateViewport();
		void cge_ConstructFontSheet();
		void cge_CoreUpdate();
		void cge_PrepareEngine();
		void cge_UpdateMouseState(int32_t button, bool state);
		void cge_UpdateKeyState(int32_t key, bool state);
		void cge_UpdateMouseFocus(bool state);
		void cge_UpdateKeyFocus(bool state);
		void cge_Terminate();
		void cge_Reanimate();
		bool cge_IsRunning();

    // At the very end of this file, chooses which
		// components to compile
		virtual void cge_ConfigureSystem();
  };
} // namespace cge


// O------------------------------------------------------------------------------O
// | START OF CGE_PGE_APPLICATION                                                 |
// O------------------------------------------------------------------------------O
// #ifdef CGE_PGE_APPLICATION
// #undef CGE_PGE_APPLICATION

namespace cge
{
  Pixel::Pixel()
  { r = 0; g = 0; b = 0; a = nDefaultAlpha; }

  Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
	{ n = red | (green << 8) | (blue << 16) | (alpha << 24); } // Thanks jarekpelczar 

	Pixel::Pixel(uint32_t p)
	{ n = p; }

  bool Pixel::operator==(const Pixel& p) const
	{ return n == p.n; }

	bool Pixel::operator!=(const Pixel& p) const
	{ return n != p.n; }

	Pixel  Pixel::operator * (const float i) const
	{
		float fR = std::min(255.0f, std::max(0.0f, float(r) * i));
		float fG = std::min(255.0f, std::max(0.0f, float(g) * i));
		float fB = std::min(255.0f, std::max(0.0f, float(b) * i));
		return Pixel(uint8_t(fR), uint8_t(fG), uint8_t(fB), a);
	}

	Pixel  Pixel::operator / (const float i) const
	{
		float fR = std::min(255.0f, std::max(0.0f, float(r) / i));
		float fG = std::min(255.0f, std::max(0.0f, float(g) / i));
		float fB = std::min(255.0f, std::max(0.0f, float(b) / i));
		return Pixel(uint8_t(fR), uint8_t(fG), uint8_t(fB), a);
	}

	Pixel& Pixel::operator *=(const float i)
	{
		this->r = uint8_t(std::min(255.0f, std::max(0.0f, float(r) * i)));
		this->g = uint8_t(std::min(255.0f, std::max(0.0f, float(g) * i)));
		this->b = uint8_t(std::min(255.0f, std::max(0.0f, float(b) * i)));
		return *this;
	}

	Pixel& Pixel::operator /=(const float i)
	{
		this->r = uint8_t(std::min(255.0f, std::max(0.0f, float(r) / i)));
		this->g = uint8_t(std::min(255.0f, std::max(0.0f, float(g) / i)));
		this->b = uint8_t(std::min(255.0f, std::max(0.0f, float(b) / i)));
		return *this;
	}

	Pixel  Pixel::operator + (const Pixel& p) const
	{
		uint8_t nR = uint8_t(std::min(255, std::max(0, int(r) + int(p.r))));
		uint8_t nG = uint8_t(std::min(255, std::max(0, int(g) + int(p.g))));
		uint8_t nB = uint8_t(std::min(255, std::max(0, int(b) + int(p.b))));
		return Pixel(nR, nG, nB, a);
	}

	Pixel  Pixel::operator - (const Pixel& p) const
	{
		uint8_t nR = uint8_t(std::min(255, std::max(0, int(r) - int(p.r))));
		uint8_t nG = uint8_t(std::min(255, std::max(0, int(g) - int(p.g))));
		uint8_t nB = uint8_t(std::min(255, std::max(0, int(b) - int(p.b))));
		return Pixel(nR, nG, nB, a);
	}

	Pixel& Pixel::operator += (const Pixel& p)
	{
		this->r = uint8_t(std::min(255, std::max(0, int(r) + int(p.r))));
		this->g = uint8_t(std::min(255, std::max(0, int(g) + int(p.g))));
		this->b = uint8_t(std::min(255, std::max(0, int(b) + int(p.b))));
		return *this;
	}

	Pixel& Pixel::operator -= (const Pixel& p) // Thanks Au Lit
	{
		this->r = uint8_t(std::min(255, std::max(0, int(r) - int(p.r))));
		this->g = uint8_t(std::min(255, std::max(0, int(g) - int(p.g))));
		this->b = uint8_t(std::min(255, std::max(0, int(b) - int(p.b))));
		return *this;
	}

	Pixel Pixel::inv() const
	{
		uint8_t nR = uint8_t(std::min(255, std::max(0, 255 - int(r))));
		uint8_t nG = uint8_t(std::min(255, std::max(0, 255 - int(g))));
		uint8_t nB = uint8_t(std::min(255, std::max(0, 255 - int(b))));
		return Pixel(nR, nG, nB, a);
	}

  CozyGameEngine::CozyGameEngine()
	{
		AppName = "Undefined";

		// Bring in relevant Platform & Rendering systems depending
		// on compiler parameters
		cge_ConfigureSystem();
	}

	CozyGameEngine::~CozyGameEngine()
	{}

  cge::rcode CozyGameEngine::Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h, bool full_screen, bool vsync)
  {
		vScreenSize = { screen_w, screen_h };
		vInvScreenSize = { 1.0f / float(screen_w), 1.0f / float(screen_h) };
		vPixelSize = { pixel_w, pixel_h };
		vWindowSize = vScreenSize * vPixelSize;
		bFullScreen = full_screen;
		bEnableVSYNC = vsync;
		vPixel = 2.0f / vScreenSize;

		if (vPixelSize.x <= 0 || vPixelSize.y <= 0 || vScreenSize.x <= 0 || vScreenSize.y <= 0)
			return cge::FAIL;
		return cge::OK;
  }
  
  // continue at 1716

} // namespace cge


